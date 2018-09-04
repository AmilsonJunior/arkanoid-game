#pragma once
#include <SFML\Graphics.hpp>
#include "Utils.h"

class IEntity
{
public:
	IEntity() {}
	virtual ~IEntity ()
	{
	}

	virtual void Render(sf::RenderWindow& render, float dt) {}
	virtual void HandleInput(sf::Event& event) {}

	virtual std::string GetId() const 
	{
		return m_entityId;
	}

	virtual void SetId(std::string id) 
	{
		m_entityId = id; 
	}

	virtual bool IsKeyPressed(sf::Event& event)
	{
		return event.type == sf::Event::KeyPressed;
	}

	virtual bool IsKeyReleased(sf::Event& event)
	{
		return event.type == sf::Event::KeyReleased;
	}

	void SetRemoved(bool b) { m_bRemoved = b; }
	bool IsRemoved() const { return m_bRemoved; }
protected:
	std::string m_entityId;
	bool m_bRemoved = false;
};