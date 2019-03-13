#include "stdafx.hpp"
#include "EvilKnights.hpp"

namespace Level {
	EvilKnights::EvilKnights() : Level(pWindow, pLevel), mIsAttacking(false)
	{
	}

	EvilKnights::EvilKnights(sf::RenderWindow* window, std::stack<Level*>* level) : Level(window, level)
	{
		this->initTextures();

		this->createMovementComponent(350.f, 16.f, 6.f);
		this->createAnimationComponent(this->mKnightTexture);

		this->pAnimationComponent->addAnimation("WALK", 10.f, 0, 0, 6, 0, 192, 192);
		this->pAnimationComponent->addAnimation("ATTACK", 10.f, 0, 1, 7, 1, 192, 192);

		this->pPlayer.setPosition(sf::Vector2f(0.F, 825.F));
	}

	EvilKnights::~EvilKnights() = default;

	void EvilKnights::updatePlayerInput(const float & deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->pPlayer.move(1.F, 0.F, deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->pPlayer.move(-1.F, 0.F, deltaTime);
	}

	void EvilKnights::update(const float & deltaTime)
	{
		this->updatePlayerInput(deltaTime);

		this->pPlayer.update(deltaTime);

		this->pMovementComponent->update(deltaTime);

		this->collision(deltaTime);

		this->mKnightSprite.move(-0.7F, 0.F);

		this->updateAnimations(deltaTime);
	}

	void EvilKnights::render(sf::RenderTarget * target)
	{
		target->draw(this->mLevelSprite);
		target->draw(this->mKnightSprite);
		this->pPlayer.render(this->pWindow);
	}

	void EvilKnights::initTextures()
	{
		if (!this->mKnightTexture.loadFromFile("Resources/Textures/KnightsEvil/Combined.png"))
			std::cerr << "Knights failed to fucking load" << "\n";

		this->mKnightSprite.setTexture(this->mKnightTexture);
		this->mKnightSprite.setPosition(1200.F, 825.F);
		this->mKnightSprite.setScale(-1.F, 1.F);

		if (!this->mLevelTexture.loadFromFile("Resources/Textures/Backgrounds/CastleBackground1.png"))
			std::cerr << "Castle failed to load" << "\n";

		this->mLevelSprite.setTexture(this->mLevelTexture);
	}

	void EvilKnights::updateAnimations(const float & deltaTime)
	{
		this->pAnimationComponent->play("WALK", deltaTime,
			this->pMovementComponent->getVelocity().x,
			this->pMovementComponent->getMaxVelocity());

		if (this->pMovementComponent->getState(ATTACK))
			this->pAnimationComponent->play("ATTACK", deltaTime);
	}

	void EvilKnights::move(const float direction_x, const float direction_y, const float & deltaTime)
	{
		if (this->pMovementComponent)
			this->pMovementComponent->move(direction_x, direction_y, deltaTime);
	}

	void EvilKnights::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
	{
		this->pMovementComponent = new MovementComponent(this->mKnightSprite, max_velocity, acceleration,
			deceleration);
	}

	void EvilKnights::createAnimationComponent(sf::Texture & texture_sheet)
	{
		this->pAnimationComponent = new AnimationComponent(this->mKnightSprite, texture_sheet);
	}

	bool EvilKnights::collision(const float & deltaTime)
	{
		if (this->mKnightSprite.getGlobalBounds().intersects(this->pPlayer.getGobalBounds()))
		{
			this->mIsAttacking = true;
			this->attack(deltaTime);
		}

		return false;
	}

	void EvilKnights::attack(const float & deltaTime)
	{
		if (this->mIsAttacking)
		{
			this->mIsAttacking = true;

			if (this->mKnightSprite.getScale().x > 0.f) //Facing left
				this->mKnightSprite.setOrigin(96.f, 0.f);

			if (this->pAnimationComponent->play("ATTACK", deltaTime, true))
			{
				this->mIsAttacking = false;

				if (this->mKnightSprite.getScale().x > 0.f) //Facing left
					this->mKnightSprite.setOrigin(0.f, 0.f);

				else //Facing right
					this->mKnightSprite.setOrigin(258.f, 0.f);
			}
		}
	}
}