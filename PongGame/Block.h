#pragma once

#include "IEntity.h"
#include "Ball.h"
#include <guid.hpp>

class Block : public IEntity
{
	sf::RectangleShape m_rectShape;
public:
	Block()
	{
		float width = 20;
		float height = 8;

		m_rectShape.setFillColor(sf::Color::White);
		m_rectShape.setSize(sf::Vector2f(width, height));
		m_rectShape.setOrigin(sf::Vector2f(width / 2, height / 2));
		m_rectShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		SetId("block-" + xg::newGuid().str());
	}

	~Block() = default;

	void SetPosition(float x, float y)
	{
		m_rectShape.setPosition(sf::Vector2f(x, y));
	}

	sf::Vector2f GetSize() { return m_rectShape.getSize(); }

	virtual void Render(sf::RenderWindow& render, float dt) override
	{
		render.draw(m_rectShape);
		Update(dt);
	}

protected:
	void Update(float dt)
	{
		if (Ball* ball = dynamic_cast<Ball*>(gEnv.GetEntityManager()->Get("Ball")))
		{
			if (m_rectShape.getGlobalBounds().intersects(ball->GetShape().getGlobalBounds()))
			{
				ball->HandleBlockCollision();
				gEnv.GetGameRules()->OnHitBlock();
				gEnv.GetEntityManager()->Remove(this->GetId());
			}
		}
	}
};

class BlockSpawner
{
public:
	static void SpawnBlocks()
	{
		float next_y_pos = 0.0f;
		
		for (int lines = 0; lines < 10; lines++)
		{
			float next_x_pos = 0.0f;
			
			if (lines == 0)
				next_y_pos = 100;
			else
				next_y_pos += 15.f;

			for(int i = 0; i < 50; i++)
			{
				Block* block = new Block();
				next_x_pos += (block->GetSize().x / 2) + 15;

				block->SetPosition(next_x_pos, next_y_pos);

				gEnv.GetEntityManager()->Add(block);
			}
		}
	}
};