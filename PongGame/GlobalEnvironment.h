#pragma once

#include "EntityManager.h"
#include "GameWindow.h"
#include "GameRules.h"

class GlobalEnvironment
{
	GlobalEnvironment()
	{
		p_entity_manager_ = new EntityManager();
		p_game_window_ = new GameWindow();
		p_game_rules_ = new GameRules();
	}
public:
	~GlobalEnvironment()
	{
		delete p_entity_manager_;
		delete p_game_rules_;
		delete p_game_window_;
	}

	static GlobalEnvironment& GetInstance()
	{
		static GlobalEnvironment genv;
		return genv;
	}

	EntityManager* GetEntityManager() const { return p_entity_manager_; }
	GameWindow* GetGameWindow() const { return p_game_window_; }
	GameRules* GetGameRules() const { return p_game_rules_; }

private:
	EntityManager* p_entity_manager_;
	GameWindow* p_game_window_;
	GameRules* p_game_rules_;
};

#define gEnv GlobalEnvironment::GetInstance()