#include "GameRules.h"
#include <iostream>

GameRules::GameRules()
	: m_score(0),
	m_gameOver(false)
{
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setPosition(30, 30);
	m_scoreText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_scoreText.setCharacterSize(20);

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Failed to load arial.ttf font\n";
	}

	m_scoreText.setFont(font);
}

void GameRules::Render(sf::RenderWindow* render)
{
	if (m_gameOver)
	{
		// Handle game over
		OnGameOver(*render);
	}
	else
	{
		// Game not over
		
	}

	render->draw(m_scoreText);
}

void GameRules::OnGameOver(sf::RenderWindow& render)
{

}

void GameRules::OnHitBlock()
{
	m_score++;
	m_scoreText.setString("Score: " + std::to_string(m_score));
}

void GameRules::OnHitBottom()
{
	if (m_score == 0)
	{
		m_gameOver = true;
		return;
	}

	m_score--;

	m_scoreText.setString("Score: " + std::to_string(m_score));
}