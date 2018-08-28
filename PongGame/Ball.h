#pragma once

#include <iostream>
#include <mutex>
#include "IEntity.h"
#include "EntityManager.h"
#include "GlobalEnvironment.h"

class Ball : public IEntity
{
	sf::CircleShape m_ballShape;
	std::once_flag spawnFlagOnce;
	float radius;
	float velocity;
	sf::Vector2f m_dir;
public:
	Ball()
	{
		SetId("Ball");

		radius = 3.5f;

		m_ballShape.setFillColor(sf::Color::Cyan);
		m_ballShape.setRadius(radius);
		//m_ballShape.setOrigin(radius / 2, radius / 2);

		m_dir.x = 10.f;
		m_dir.y = 10.f;

		velocity = 10.0f;
	}

	~Ball() = default;

	virtual void Render(sf::RenderWindow& render, float dt) override
	{
		std::call_once(spawnFlagOnce, [&]()
		{
			m_ballShape.setPosition(render.getView().getSize().x / 2, render.getView().getSize().y / 2);
		});

		UpdateMovement(render, dt);

		render.draw(m_ballShape);
	}

	void HandleBlockCollision()
	{
		m_dir.y < 0 ? m_dir.y = abs(velocity) : m_dir.y = -velocity;
	}

	sf::Vector2f GetPosition() { return m_ballShape.getPosition(); }
	sf::CircleShape& GetShape() { return m_ballShape; }
protected:
	void UpdateMovement(sf::RenderWindow& render, float dt)
	{
		HandleBorderCollision(render.getView().getSize().x, render.getView().getSize().y, dt);
		HandlePaddleCollision(dt);

		m_ballShape.move(m_dir.x, m_dir.y);
	}

	void HandlePaddleCollision(float dt)
	{
		if (Paddle* paddle = dynamic_cast<Paddle*>(gEnv.GetEntityManager()->Get("Paddle01")))
		{
			if (paddle->GetShape().getGlobalBounds().contains(m_ballShape.getPosition()))
			{
				m_dir.y < 0 ? m_dir.y = abs(velocity) : m_dir.y = -velocity;
			}
		}
	}

	void HandleBorderCollision(float width, float height, float dt)
	{
		if (m_ballShape.getPosition().x + radius >= width) //RIGHT
		{
			m_dir.x = -velocity;
		}
		else if (m_ballShape.getPosition().x + radius <= 0) //LEFT
		{
			m_dir.x = velocity;
		}
		else if (m_ballShape.getPosition().y + radius <= 0) //TOP
		{
			m_dir.y = velocity;
		}
		else if (m_ballShape.getPosition().y + radius >= height) //BOTTOM
		{
			m_dir.y = -velocity;

			gEnv.GetGameRules()->OnHitBottom();
		}
	}
};
