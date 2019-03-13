#pragma once
class States
{
public:
	States(sf::RenderWindow* window, std::stack<States*>* states);
	void endState();

	virtual void updateMousePositions();
	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	sf::RenderWindow* pWindow;
	sf::Vector2i pMousePositionScreen;
	sf::Vector2i pMousePositionWindow;
	sf::Vector2f pMousePositionView;

	std::stack<States*>* mStates;

	bool pQuit;
};