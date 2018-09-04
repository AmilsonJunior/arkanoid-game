#include "GameWindow.h"
#include "GameRules.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "GameFactory.h"
#include "EntityManager.h"

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::InitializeFactory()
{
	m_pWindow.create(sf::VideoMode(1024, 768), "Pong Game");
	m_pWindow.setFramerateLimit(60);
	
	GameFactory::Initialize();
}

void GameWindow::Run()
{
	m_pCurrentState = INTIALIZING;

	InitializeFactory();

	while (m_pCurrentState != CLOSING)
	{
		sf::Event event;

		EventLoop(event);
		UpdateLoop();
	}
}

void GameWindow::UpdateLoop()
{
	m_pWindow.clear(sf::Color::Black);

	float dt = m_clock.getElapsedTime().asMilliseconds();

	gEnv.GetGameRules()->Render(&m_pWindow);
	gEnv.GetEntityManager()->Render(m_pWindow, dt);

	m_clock.restart().asMilliseconds();

	m_pWindow.display();
}

void GameWindow::EventLoop(sf::Event & event)
{
	while (m_pWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_pCurrentState = CLOSING;
		}

		gEnv.GetEntityManager()->HandleInput(event);

		if (event.type == event.KeyPressed)
		{
			HandleGlobalInput(event);	
		}
	}
}

void GameWindow::HandleGlobalInput(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		std::cout << "Esc pressed\n";
	}
}
