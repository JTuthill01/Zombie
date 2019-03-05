#include "stdafx.hpp"
#include "Zombies.hpp"

namespace Level
{
	Zombies::Zombies() : Level(pWindow, pLevel), mPlayerPosition(false)
	{
	}

	Zombies::Zombies(sf::RenderWindow* window, std::stack<Level*>* level) : Level(window, level), mPlayerPosition(false)
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

		if (mPlayerPosition == false)
		{
			this->mPlayer.setPosition(sf::Vector2f(0, 750));
			//this->mPlayer.setLoadLevel(false);
			mPlayerPosition = true;
		}
	}
}