#include "stdafx.hpp"
#include "Orc.hpp"

namespace Level
{
	Orc::Orc() : Level(pWindow, pLevel), mIsAttacking(false) {}

	Orc::Orc(sf::RenderWindow* window, std::stack<Level*>* level) : Level(window, level), mIsAttacking(false), mIsWalking(true)
	{
		this->initTextures();

		this->createMovementComponent(350.f, 16.f, 6.f);
		this->createAnimationComponent(this->mOrcTexture);

		this->pAnimationComponent->addAnimation("WALK", 5.f, 0, 0, 6, 0, 192, 192);
		this->pAnimationComponent->addAnimation("ATTACK", 5.f, 0, 1, 6, 1, 192, 192);

		this->pPlayer.setPosition(sf::Vector2f(0.F, 700.F));
	}

	Orc::~Orc() = default;

	void Orc::update(const float & deltaTime)
	{
		this->mOrcSprite.move(sf::Vector2f(-0.5F, 0.F));

		this->pPlayer.update(deltaTime);

		this->pMovementComponent->update(deltaTime);

		this->collision(deltaTime);

		this->updateAnimations(deltaTime);

		this->updatePlayerInput(deltaTime);

		if (this->pPlayer.isLoadLevel() == false)
		{
			if (this->pPlayer.getPosition().x > this->pWindow->getSize().x)
			{
				this->pLevel->push(new Zombies(this->pWindow, this->pLevel));

				this->pPlayer.setLoadLevel(true);
			}
		}
	}

	void Orc::render(sf::RenderTarget * target)
	{
		target->draw(this->mLevelSprite);
		target->draw(this->mOrcSprite);

		this->pPlayer.render(this->pWindow);
	}

	void Orc::initTextures()
	{
		if (!this->mOrcTexture.loadFromFile("Resources/Textures/Orcs/Combined.png"))
			std::cerr << "Orc failed to load, so yeah fuck you" << "\n";

		if (!this->mLeveltexture.loadFromFile("Resources/Textures/Backgrounds/bitmap.png"))
			std::cerr << "Orc Level failed to load asshole" << "\n";

		if (!this->mFont.loadFromFile("Resources/Fonts/Metropolian-Display.ttf"))
			std::cerr << "Font failed to fucking load";

		this->mOrcSprite.setTexture(this->mOrcTexture);
		this->mOrcSprite.setScale(-1.F, 1.F);

		this->mOrcSprite.setPosition(1700, 700);
		this->mLevelSprite.setTexture(this->mLeveltexture);
	}

	void Orc::updateAnimations(const float & deltaTime)
	{
		if (!this->collision(deltaTime))
		{
			if (this->mIsWalking)
			{
				if (this->pMovementComponent->getState(MOVING))
				{
					if (this->mOrcSprite.getScale().x < 0.f)
					{
						this->mOrcSprite.setOrigin(0.f, 0.f);
						this->mOrcSprite.setScale(-1.f, 1.f);
					}

					this->pAnimationComponent->play("WALK", deltaTime,
						this->pMovementComponent->getVelocity().x,
						this->pMovementComponent->getMaxVelocity());
				}
			}
		}

		if (this->collision(deltaTime))
		{
			this->mIsAttacking = true;
			this->mIsWalking = false;
		
			if (this->mIsAttacking)
			{
				if (this->mOrcSprite.getScale().x > 0.f) //Facing left
					this->mOrcSprite.setOrigin(96.f, 0.f);

				if (this->pAnimationComponent->play("ATTACK", deltaTime, true))
				{
					this->mIsWalking = true;
					this->mIsAttacking = false;
				}
			}
		}
	}

	void Orc::move(const float direction_x, const float direction_y, const float & deltaTime)
	{
		if (this->pMovementComponent)
			this->pMovementComponent->move(direction_x, direction_y, deltaTime);
	}

	bool Orc::collision(const float & deltaTime)
	{
		if (this->mOrcSprite.getGlobalBounds().intersects(this->pPlayer.getGobalBounds()))
			return true;

		return false;
	}

	void Orc::attack(const float & deltaTime)
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

	void Orc::updatePlayerInput(const float & deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->pPlayer.move(1.F, 0.F, deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->pPlayer.move(-1.F, 0.F, deltaTime);
	}
}