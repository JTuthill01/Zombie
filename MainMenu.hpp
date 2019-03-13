#pragma once
#include "GameState.hpp"
#include "States.hpp"
#include "Button.hpp"

class MainMenu :
	public States
{
public:
	MainMenu();
	MainMenu(sf::RenderWindow* window, std::stack<States*>* states);
	~MainMenu();

	// Inherited via States
	virtual void update(const float & deltaTime) override;
	virtual void render(sf::RenderTarget * target = nullptr) override;

private:
	void initTextures();
	void initFonts();
	void createButtons();
	void renderButtons(sf::RenderTarget* target);

	sf::Font mFont;
	sf::Texture mBackgroundTexture;
	sf::Sprite mBackgroundSprite;
	sf::Event e;

	std::map<std::string, Button*> mButton;
};