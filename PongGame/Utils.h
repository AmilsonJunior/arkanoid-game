#pragma once

#include <SFML/Graphics.hpp>

class Utils
{
public:
	static void PrintVector2f(const sf::Vector2f& vec, std::string message = "")
	{
		printf("%s {x: %.2f, y: %0.2f}\n", message.c_str(), vec.x, vec.y);
	}
};