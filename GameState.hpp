#pragma once
#include "States.hpp"
#include "Player.hpp"
#include "Orc.hpp"

class GameState :
	public States
{
public:
	GameState(sf::RenderWindow* window, std::stack<States*>* states);
	virtual ~GameState();

	// Inherited via States
	virtual void update(const float & deltaTime) override;
	virtual void render(sf::RenderTarget * target = nullptr) override;

	void updatePlayerInput(const float& deltaTime);
	void initLevel();

private:

	sf::Texture mBackgroundTexture;
	sf::Sprite mBackgroundSprite;

	std::stack<Level::Level*> mLevels;

	Player mPlayer;
	Level::Orc mOrc;
};

