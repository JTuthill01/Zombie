#include "stdafx.hpp"
#include "Game.hpp"

Game::Game() : isClosed(false)
{
	this->initWindow();
	this->initStates();
}
Game::~Game()
{
	delete this->mWindow;

	while (!this->mStates.empty())
	{
		delete this->mStates.top();
		this->mStates.pop();
	}
}

void Game::run()
{
	while (this->mWindow->isOpen())
	{
		this->updateDeltaTime();
		this->update(mDeltaTime);
		this->render();
	}
}

void Game::initWindow()
{
	this->mWindow = new sf::RenderWindow(sf::VideoMode(1920, 1098),
		"Zombie Game v1.0.1");
}

void Game::render()
{
	this->mWindow->clear();

	if (!this->mStates.empty())
		this->mStates.top()->render(this->mWindow);

	this->mWindow->display();
}

void Game::update(const float & deltaTime)
{
	this->events();

	if (!this->mStates.empty())
		this->mStates.top()->update(deltaTime);
}

void Game::updateDeltaTime()
{
	this->mDeltaTime = this->mClock.restart().asSeconds();
}

void Game::initStates()
{
	this->mStates.push(new MainMenu(this->mWindow, &this->mStates));
}

void Game::events()
{
	while (this->mWindow->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			this->mWindow->close();
	}
}

