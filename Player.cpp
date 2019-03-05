#include "stdafx.hpp"
#include "Player.hpp"

Player::Player() : mIsAttacking(false)
{
	this->initTextures();

	this->createMovementComponent(350.f, 16.f, 6.f);
	this->createAnimationComponent(this->mPlayerTexture);

	this->pAnimationComponent->addAnimation("IDLE", 10.f, 0, 0, 9, 0, 192, 192);
	this->pAnimationComponent->addAnimation("WALK", 5.f, 0, 1, 9, 1, 192, 192);
	this->pAnimationComponent->addAnimation("JUMP", 5.f, 0, 1, 9, 1, 192, 192);
	this->pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 2, 9, 2, 192, 192);
}

Player::~Player()
{
}

void Player::render(sf::RenderTarget * target)
{
	target->draw(this->mPlayerSprite);
}

void Player::update(const float & deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->mIsAttacking = true;

	this->pMovementComponent->update(deltaTime);

	this->updateAttack();

	this->updateAnimations(deltaTime);
}

void Player::updateAnimations(const float & deltaTime)
{
	if (this->IsAttacking())
	{
		if (this->mPlayerSprite.getScale().x > 0.f) //Facing left
			this->mPlayerSprite.setOrigin(96.f, 0.f);

		else //Facing right
			this->mPlayerSprite.setOrigin(350.f, 0.f);

		if (this->pAnimationComponent->play("ATTACK", deltaTime, true))
		{
			this->mIsAttacking = false;

			if (this->mPlayerSprite.getScale().x > 0.f) //Facing left
				this->mPlayerSprite.setOrigin(0.f, 0.f);


			else //Facing right
				this->mPlayerSprite.setOrigin(258.f, 0.f);
		}
	}

	if (this->pMovementComponent->getState(IDLE))
		this->pAnimationComponent->play("IDLE", deltaTime);


	else	if (this->pMovementComponent->getState(MOVING_RIGHT))
	{
		if (this->mPlayerSprite.getScale().x < 0.f)
		{
			this->mPlayerSprite.setOrigin(0.f, 0.f);
			this->mPlayerSprite.setScale(1.f, 1.f);
		}

		this->pAnimationComponent->play("WALK", deltaTime,
			this->pMovementComponent->getVelocity().x,
			this->pMovementComponent->getMaxVelocity());
	}


	else if (this->pMovementComponent->getState(MOVING_LEFT))
	{
		if (this->mPlayerSprite.getScale().x > 0.f)
		{
			this->mPlayerSprite.setOrigin(140.f, 0.f);
			this->mPlayerSprite.setScale(-1.f, 1.f);
		}

		this->pAnimationComponent->play("WALK", deltaTime,
			this->pMovementComponent->getVelocity().x,
			this->pMovementComponent->getMaxVelocity());
	}

	else if (this->pMovementComponent->getState(MOVING_UP))
		this->pAnimationComponent->play("JUMP", deltaTime,
			this->pMovementComponent->getVelocity().y,
			this->pMovementComponent->getMaxVelocity());

	/*else if (this->pMovementComponent->getState(FALLING_DOWN))
		this->pAnimationComponent->play("WALK", deltaTime,
			this->pMovementComponent->getVelocity().y,
			this->pMovementComponent->getMaxVelocity());*/
}

void Player::move(const float direction_x, const float direction_y, const float & deltaTime)
{
	if (this->pMovementComponent)
		this->pMovementComponent->move(direction_x, direction_y, deltaTime);
}

void Player::initTextures()
{
	if (!this->mPlayerTexture.loadFromFile("Resources/Textures/Player/NewCombined.png"))
		std::cerr << "Fuck, the texture failed to load" << "\n";

	this->mPlayerSprite.setTexture(this->mPlayerTexture);
	this->mPlayerSprite.setPosition(sf::Vector2f(700, 700));
}

void Player::updateAttack()
{
}

void Player::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
{
	this->pMovementComponent = new MovementComponent(this->mPlayerSprite, max_velocity, acceleration,
		deceleration);
}

void Player::createAnimationComponent(sf::Texture & texture_sheet)
{
	this->pAnimationComponent = new AnimationComponent(this->mPlayerSprite, texture_sheet);
}
