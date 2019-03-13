#include "stdafx.hpp"
#include "MainMenu.hpp"

MainMenu::MainMenu() : States(this->pWindow, this->mStates)
{
}

MainMenu::MainMenu(sf::RenderWindow* window, std::stack<States*>* states) : States(window, states)
{
	this->initTextures();
	this->initFonts();
	this->createButtons();
}

MainMenu::~MainMenu()
{
}

void MainMenu::update(const float & deltaTime)
{
	this->updateMousePositions();

	if (this->mButton["Exit"]->isPressed(pMousePositionView))
		this->pWindow->close();

	if (this->mButton["Play"]->isPressed(pMousePositionView))
		this->mStates->push(new GameState(this->pWindow, this->mStates));
}

void MainMenu::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->pWindow;

	target->draw(this->mBackgroundSprite);

	this->renderButtons(target);
}

void MainMenu::initTextures()
{
	if (!this->mBackgroundTexture.loadFromFile("Resources/Textures/Backgrounds/postapocalypse3_1.png"))
		std::perror("Failed to load");

	this->mBackgroundSprite.setTexture(this->mBackgroundTexture);
}

void MainMenu::initFonts()
{
	if (!this->mFont.loadFromFile("Resources/Fonts/Anton-Regular.ttf"))
		std::cerr << "Font failed to load" << "\n";
}

void MainMenu::createButtons()
{
	this->mButton["Play"] = new Button(sf::Vector2f(400.F, 600.F), 150.F, 50.F, &this->mFont, "Play", 20U, sf::Color(106, 114, 109, 250), sf::Color::White);
	this->mButton["Exit"] = new Button(sf::Vector2f(400.F, 700.F), 150.F, 50.F, &this->mFont, "Pussy out", 20U, sf::Color(106, 114, 109, 250), sf::Color::White);
}

void MainMenu::renderButtons(sf::RenderTarget* target)
{
	for (auto &it : this->mButton)
		it.second->render(*target);
}