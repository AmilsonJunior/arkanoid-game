#pragma once

#include <SFML/Graphics.hpp>
#include <mutex>

class GameRules
{
	int m_score;
	bool m_gameOver;
	sf::Text m_scoreText;
	std::once_flag flag;
	sf::Font font;
public:
	GameRules();

	void Render(sf::RenderWindow* render);
	void OnGameOver(sf::RenderWindow& render);
	void OnHitBlock();
	void OnHitBottom();
};
