#pragma once

class Button
{
public:
	Button(sf::Vector2f position, float width, float height, sf::Font* font, std::string text, 
		unsigned character_size, sf::Color buttonColor, sf::Color textColor);
	~Button();

	void render(sf::RenderTarget& target);

	const bool isPressed(const sf::Vector2f mousePosition) const;

private:
	sf::Font* mFont;
	sf::Text mText;
	sf::RectangleShape mShape;
	sf::Color mButtonColor;
	sf::Color mTextColor;
	sf::Vector2f mPosition;

	float mWidth;
	float mHeight;

	unsigned short mButtonState;
};

