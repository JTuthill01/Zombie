#pragma once
class TextTags
{
public:
	TextTags(sf::Font* font, std::string text, sf::Vector2f position, sf::Vector2f direction, sf::Color textColor, float maxTime, unsigned size);
	virtual ~TextTags();

	void render(sf::RenderTarget* target);
	void update(const float& deltaTime);

private:
	sf::Text mText;
	sf::Font mFont;
	sf::Vector2f mPosition;
	sf::Vector2f mDirection;
	sf::Color mColor;

	float mDeltaTimeMultiplier;
	float mSpeed;
	float mMaxTime;
	float mTimer;

	unsigned mSize;
};