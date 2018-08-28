#pragma once
#include "IEntity.h"
#include "GlobalEnvironment.h"

constexpr float maxSpeed = 60.f;

class Paddle : public IEntity
{
	sf::RectangleShape m_rectShape;
	float velocity;
	unsigned int inputFlag;

	enum
	{
		MOVE_LEFT = 1,
		MOVE_RIGHT,
		NO_MOVE
	};

public:
	Paddle()
		: velocity(0.0f), inputFlag(0)
	{
		IEntity::SetId("Paddle01");

		float width = 100.f;
		float height = 10.f;

		m_rectShape.setSize(sf::Vector2f(width, height));
		m_rectShape.setFillColor(sf::Color::White);
		m_rectShape.setOrigin(sf::Vector2f(width / 2, height / 2));
		m_rectShape.setPosition(gEnv.GetGameWindow()->GetRenderWindow().getView().getSize().x / 2,
		                        gEnv.GetGameWindow()->GetRenderWindow().getView().getSize().y - 100);
	}

	~Paddle() = default;

	virtual void Render(sf::RenderWindow& render, float dt) override
	{
		UpdateMovement(render, dt);

		render.draw(m_rectShape);
	}

	virtual void HandleInput(sf::Event& event) override
	{
		if (IsKeyPressed(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				inputFlag = MOVE_LEFT;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				inputFlag = MOVE_RIGHT;
			}
		}

		else if (IsKeyReleased(event))
		{
			inputFlag = NO_MOVE;
		}
	}

	sf::RectangleShape GetShape() const { return m_rectShape; }

private:
	void UpdateMovement(sf::RenderWindow& render, float dt)
	{
		if (inputFlag == MOVE_LEFT)
		{
			if ((m_rectShape.getPosition().x - 5.f - velocity - (m_rectShape.getSize().x / 2)) > 0)
				velocity = -16;
			else
				velocity = 0;
		}
		else if (inputFlag == MOVE_RIGHT)
		{
			if ((m_rectShape.getPosition().x + 5.f + velocity + m_rectShape.getSize().x / 2) < render.getView().getSize().x)
				velocity = 16;
			else
				velocity = 0;
		}
		else if (inputFlag == NO_MOVE)
		{
			if (velocity > 0 && velocity <= maxSpeed)
				velocity -= 0.8f;
			else if (velocity < 0 && velocity >= -maxSpeed)
				velocity += 0.8f;
		}

		m_rectShape.move(velocity, 0);
	}
};