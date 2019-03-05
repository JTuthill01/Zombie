#pragma once
#include "Player.hpp"

namespace Level
{
	class Level
	{
	public:
		Level(sf::RenderWindow* window, std::stack<Level*>* level);
		~Level();

		virtual void update(const float& deltaTime) = 0;
		virtual void render(sf::RenderTarget* target) = 0;
		virtual void initTextures() = 0;

	protected:
		sf::RenderWindow* pWindow;

		Player pPlayer;

		std::stack <Level*>* pLevel;
	};

}