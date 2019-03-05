#pragma once
#include "Level.hpp"

namespace Level
{
	class Zombies :
		public Level
	{
	public:
		Zombies();
		Zombies(sf::RenderWindow* window, std::stack<Level*>* level);
		virtual ~Zombies();

		// Inherited via Level
		virtual void render(sf::RenderTarget * target) override;
		virtual void initTextures() override;
		virtual void update(const float & deltaTime) override;

	private:
		Player mPlayer;
		bool mPlayerPosition;

		sf::Texture mLevelTexture;
		sf::Sprite mLevelSprite;
	};
}