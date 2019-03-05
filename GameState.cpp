#include "stdafx.hpp"
#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window, std::stack<States*>* states) : States(window, states)
{
	this->initLevel();
}

GameState::~GameState()
{
	while (!this->mLevels.empty())
	{
		delete this->mLevels.top();
		this->mLevels.pop();
	}
}

void GameState::update(const float & deltaTime)
{
	this->mPlayer.update(deltaTime);
	this->updatePlayerInput(deltaTime);

	if (this->mPlayer.isLoadLevel() == false)
	{
		if (this->mPlayer.getPosition().x > this->pWindow->getSize().x)
		{
			this->mLevels.emplace(new Level::Zombies(this->pWindow, &this->mLevels));
			this->mPlayer.setLoadLevel(true);
		}
	}

	if (!this->mLevels.empty())
		this->mLevels.top()->update(deltaTime);
}

void GameState::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->pWindow;

	if (!this->mLevels.empty())
		this->mLevels.top()->render(this->pWindow);

	this->mPlayer.render(this->pWindow);
}

void GameState::updatePlayerInput(const float & deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->mPlayer.move(1.F, 0.F, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->mPlayer.move(-1.F, 0.F, deltaTime);

	std::cout << this->mPlayer.pMovementComponent->getVelocity().x << " -  " << this->mPlayer.pMovementComponent->getVelocity().x << "\n";
}

void GameState::initLevel()
{
	this->mLevels.push(new Level::Orc(this->pWindow, &this->mLevels));
}