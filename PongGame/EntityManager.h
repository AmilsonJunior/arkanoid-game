#pragma once
#include <map>
#include <SFML\System\Thread.hpp>
#include "IEntity.h"

class EntityManager
{
public:
	~EntityManager();

	static EntityManager& GetInstance()
	{
		static EntityManager entityManager;

		return entityManager;
	}

	void Add(IEntity* pEntity);
	void Remove(const std::string& id );
	void Render(sf::RenderWindow& render, float dt);
	void HandleInput(sf::Event& event);
	IEntity* Get(const std::string& id);

private:
	std::map<std::string, IEntity*> m_pEntities;
};