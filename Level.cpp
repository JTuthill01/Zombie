#include "stdafx.hpp"
#include "Level.hpp"

namespace Level 
{
	Level::Level(sf::RenderWindow* window, std::stack<Level*>* level) : pWindow(window), pLevel(level)
	{
	}

	Level::~Level()
	{
	}
}