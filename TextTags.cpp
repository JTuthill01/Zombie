#include "stdafx.hpp"
#include "TextTags.hpp"

TextTags::TextTags(sf::Font* font, std::string text, sf::Vector2f position, sf::Vector2f direction, sf::Color textColor, float maxTime, unsigned size) : mFont(*font), mPosition(position),
mDirection(direction), mColor(textColor), mMaxTime(maxTime), mSize(size), mDeltaTimeMultiplier(62.5F), mSpeed(1.2F)
{
	this->mText.setFont(*font);
	this->mText.setString(text);
	this->mText.setPosition(position);
	this->mText.setFillColor(textColor);
	this->mText.setCharacterSize(size);

	this->mTimer = maxTime;
}

TextTags::~TextTags() = default;

void TextTags::render(sf::RenderTarget * target)
{
	target->draw(this->mText);
}

void TextTags::update(const float & deltaTime)
{
	if (this->mTimer > 0.F)
	{
		this->mTimer -= 1.f * this->mDeltaTimeMultiplier * deltaTime;

		this->mText.move(this->mPosition.x * this->mDirection.x * this->mSpeed *this->mDeltaTimeMultiplier * deltaTime,
			this->mPosition.y * this->mDirection.y * this->mSpeed * this->mDeltaTimeMultiplier * deltaTime);
	}

	else
		this->mText.setFillColor(sf::Color(0, 0, 0, 255));
}