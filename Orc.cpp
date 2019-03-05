#include "stdafx.hpp"
#include "Orc.hpp"

namespace Level
{
	Orc::Orc() : Level(pWindow, pLevel)
	{
	}

	Orc::Orc(sf::RenderWindow* window, std::stack<Level*>* level) : Level(window, level)
	{
		this->initTextures();

		this->createMovementComponent(350.f, 16.f, 6.f);
		this->createAnimationComponent(this->mOrcTexture);

		this->pAnimationComponent->addAnimation("IDLE", 10.f, 0, 0, 5, 0, 192, 192);
		//this->pAnimationComponent->addAnimation("WALK", 5.f, 0, 1, 9, 1, 192, 192);
		//this->pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 2, 9, 2, 192, 192);
	}

	Orc::~Orc()
	{
	}

	void Orc::update(const float & deltaTime)
	{
		this->pMovementComponent->update(deltaTime);

		this->updateAttack();

		this->updateAnimations(deltaTime);
	}

	void Orc::render(sf::RenderTarget * target)
	{
		target->draw(this->mLevelSprite);
		target->draw(this->mOrcSprite);
	}

	void Orc::initTextures()
	{
		if (!this->mOrcTexture.loadFromFile("Resources/Textures/Orcs/OrcIdleSheet.png"))
			std::cerr << "Orc failed to load, so yeah fuck you" << "\n";

		if (!this->mLeveltexture.loadFromFile("Resources/Textures/Backgrounds/bitmap.png"))
			std::cerr << "Orc Level failed to load asshole" << "\n";

		this->mOrcSprite.setTexture(this->mOrcTexture);
		this->mOrcSprite.setPosition(900, 700);
		this->mLevelSprite.setTexture(this->mLeveltexture);
	}

	void Orc::updateAnimations(const float & deltaTime)
	{
		if (this->IsAttacking())
		{
			if (this->mOrcSprite.getScale().x > 0.f) //Facing left
				this->mOrcSprite.setOrigin(96.f, 0.f);

			else //Facing right
				this->mOrcSprite.setOrigin(350.f, 0.f);

			if (this->pAnimationComponent->play("ATTACK", deltaTime, true))
			{
				this->mIsAttacking = false;

				if (this->mOrcSprite.getScale().x > 0.f) //Facing left
					this->mOrcSprite.setOrigin(0.f, 0.f);


				else //Facing right
					this->mOrcSprite.setOrigin(258.f, 0.f);
			}
		}

		if (this->pMovementComponent->getState(IDLE))
			this->pAnimationComponent->play("IDLE", deltaTime);


		else	if (this->pMovementComponent->getState(MOVING_RIGHT))
		{
			if (this->mOrcSprite.getScale().x < 0.f)
			{
				this->mOrcSprite.setOrigin(0.f, 0.f);
				this->mOrcSprite.setScale(1.f, 1.f);
			}

			this->pAnimationComponent->play("WALK", deltaTime,
				this->pMovementComponent->getVelocity().x,
				this->pMovementComponent->getMaxVelocity());
		}


		else if (this->pMovementComponent->getState(MOVING_LEFT))
		{
			if (this->mOrcSprite.getScale().x > 0.f)
			{
				this->mOrcSprite.setOrigin(140.f, 0.f);
				this->mOrcSprite.setScale(-1.f, 1.f);
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

	void Orc::move(const float direction_x, const float direction_y, const float & deltaTime)
	{
		if (this->pMovementComponent)
			this->pMovementComponent->move(direction_x, direction_y, deltaTime);
	}

	void Orc::updateAttack()
	{

	}

	void Orc::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
	{
		this->pMovementComponent = new MovementComponent(this->mOrcSprite, max_velocity, acceleration,
			deceleration);
	}

	void Orc::createAnimationComponent(sf::Texture & texture_sheet)
	{
		this->pAnimationComponent = new AnimationComponent(this->mOrcSprite, texture_sheet);
	}
}