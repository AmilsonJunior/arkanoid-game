#include "EntityManager.h"


EntityManager::~EntityManager()
{
	for (auto& entity : m_pEntities)
	{
		delete entity.second;
	}

	m_pEntities.clear();
}

void EntityManager::Add(IEntity * pEntity)
{
	m_pEntities.insert({ pEntity->GetId(), pEntity });

	printf("EntityManager::Add: Entity \"%s\" registered successfully!\n", pEntity->GetId().c_str());
}

void EntityManager::Remove(const std::string& id)
{
	auto it = m_pEntities.find(id);

	if (it != m_pEntities.end())
	{
		it->second->SetRemoved(true);
	}
}

void EntityManager::Render(sf::RenderWindow & render, float dt)
{
	auto it = m_pEntities.begin();

	while(it != m_pEntities.end())
	{
		if (it->second->IsRemoved())
		{
			printf("EntityManager::Remove: Entity \"%s\" removed.\n", it->first.c_str());

			auto reIt = it++;
			delete reIt->second;
			m_pEntities.erase(reIt);
		}

		if (it != m_pEntities.end())
		{
			it->second->Render(render, dt);
			++it;
		}
	}
}

void EntityManager::HandleInput(sf::Event& event)
{
	for (auto& entity : m_pEntities)
	{
		entity.second->HandleInput(event);
	}
}

IEntity* EntityManager::Get(const std::string& id)
{
	auto it = m_pEntities.find(id);

	if (it != m_pEntities.end())
	{
		return it->second;
	}

	return nullptr;
}
