#include "stdafx.hpp"
#include "Zombies.hpp"

namespace Level
{
	Zombies::Zombies() : Level(pWindow, pLevel)
	{
	}

	Zombies::Zombies(sf::RenderWindow* window, std::stack<Level*>* level) : Level(window, level)
	{
		this->initTextures();
	}

	Zombies::~Zombies()
	{
		
	}

	void Zombies::render(sf::RenderTarget * target)
	{
		target->draw(this->mLevelSprite);
		this->mPlayer.render(this->pWindow);
	}

	void Zombies::initTextures()
	{
		if (!this->mLevelTexture.loadFromFile("Resources/Textures/Backgrounds/postapocalypse1.png"))
			std::cerr << "Level failed" << "\n";

		this->mLevelSprite.setTexture(this->mLevelTexture);
	}

	void Zombies::update(const float & deltaTime)
	{
		this->mPlayer.update(deltaTime);

		std::cout << deltaTime << "\n";
	}
}