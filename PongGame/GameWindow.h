#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	void Run();
	sf::RenderWindow& GetRenderWindow() { return m_pWindow; }

protected:
	void UpdateLoop();
	void EventLoop(sf::Event& event);
	void HandleGlobalInput(sf::Event& event);
	void InitializeFactory();

	enum GameState
	{
		INTIALIZING,
		RUNNING,
		PAUSED,
		CLOSING
	};


private:
	sf::RenderWindow m_pWindow;
	GameState m_pCurrentState;
	sf::Clock m_clock;
};

