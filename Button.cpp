#include "stdafx.hpp"
#include "Button.hpp"

Button::Button(sf::Vector2f position, float width, float height, sf::Font* font, std::string text,
	unsigned character_size, sf::Color buttonColor, sf::Color textColor) : mPosition(position), mWidth(width), mHeight(height),
	mFont(font), mButtonColor(buttonColor), mTextColor(textColor)
{
	this->mShape.setFillColor(buttonColor);
	this->mShape.setSize(sf::Vector2f(width, height));
	this->mShape.setPosition(position);
	this->mShape.setOutlineColor(buttonColor);
	this->mShape.setOutlineThickness(1U);

	this->mText.setFont(*this->mFont);
	this->mText.setCharacterSize(character_size);
	this->mText.setString(text);
	this->mText.setFillColor(sf::Color::White);
	this->mText.setPosition(sf::Vector2f(this->mShape.getPosition().x + (this->mShape.getGlobalBounds().width / 2.f)
		- this->mText.getGlobalBounds().width / 2.f,
		this->mShape.getPosition().y + (this->mShape.getGlobalBounds().height / 2.2f) -
		this->mText.getGlobalBounds().height / 2.f));
}

Button::~Button()
{
}

void Button::render(sf::RenderTarget & target)
{
	target.draw(this->mShape);
	target.draw(this->mText);
}

const bool Button::isPressed(const sf::Vector2f mousePosition) const
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->mShape.getGlobalBounds().contains(mousePosition))
		return true;

	return false;
}