#include "stdafx.hpp"
#include "Zombies.hpp"

namespace Level
{
	Zombies::Zombies() : Level(pWindow, pLevel)
	{
	}

	Zombies::Zombies(sf::RenderWindow* window, std::stack<Level*>* level) : Level(window, level), mIsAttacking(false)
	{
		this->initTextures();

		this->createMovementComponent(350.f, 16.f, 6.f);
		this->createAnimationComponent(this->mZombieTexture);

		this->pAnimationComponent->addAnimation("IDLE", 10.f, 0, 0, 5, 0, 192, 192);
		this->pAnimationComponent->addAnimation("ATTACK", 10.f, 0, 1, 7, 1, 192, 192);
		this->pAnimationComponent->addAnimation("WALK", 10.f, 0, 2, 8, 2, 192, 192);

		this->pPlayer.setPosition(sf::Vector2f(0.F, 750.F));
	}

	Zombies::~Zombies() = default;

	void Zombies::render(sf::RenderTarget * target)
	{
		target->draw(this->mLevelSprite);
		target->draw(this->mZombieSprite);

		this->pPlayer.render(this->pWindow);
	}

	void Zombies::initTextures()
	{
		if (!this->mLevelTexture.loadFromFile("Resources/Textures/Backgrounds/postapocalypse1.png"))
			std::cerr << "Level failed to load" << "\n";

		if (!this->mZombieTexture.loadFromFile("Resources/Textures/Zombies/Combined.png"))
			std::cerr << "Zombie texture failed to load" << "\n";

		this->mZombieSprite.setTexture(this->mZombieTexture);
		this->mZombieSprite.setPosition(1200.F, 750.F);
		this->mZombieSprite.setScale(-1.F, 1.F);

		this->mLevelSprite.setTexture(this->mLevelTexture);
	}

	void Zombies::update(const float & deltaTime)
	{
		this->mZombieSprite.move(sf::Vector2f(-0.5F, 0.F));

		this->updatePlayerInput(deltaTime);

		this->pPlayer.update(deltaTime);

		this->pMovementComponent->update(deltaTime);

		this->collision(deltaTime);

		this->updateAnimations(deltaTime);

		if (this->pPlayer.isLoadLevel() == false)
		{
			if (this->pPlayer.getPosition().x > this->pWindow->getSize().x)
			{
				this->pLevel->push(new EvilKnights(this->pWindow, this->pLevel));

				this->pPlayer.setLoadLevel(true);
			}
		}
	}

	void Zombies::updateAnimations(const float & deltaTime)
	{
		if (this->pMovementComponent->getState(MOVING))
			this->pAnimationComponent->play("WALK", deltaTime,
				this->pMovementComponent->getVelocity().x,
				this->pMovementComponent->getMaxVelocity());

		if (this->pMovementComponent->getState(ATTACK))
			this->pAnimationComponent->play("ATTACK", deltaTime);
	}

	void Zombies::move(const float direction_x, const float direction_y, const float & deltaTime)
	{
		if (this->pMovementComponent)
			this->pMovementComponent->move(direction_x, direction_y, deltaTime);
	}

	void Zombies::updatePlayerInput(const float & deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->pPlayer.move(1.F, 0.F, deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->pPlayer.move(-1.F, 0.F, deltaTime);
	}

	void Zombies::updateAttack(const float & deltaTime)
	{
	}

	void Zombies::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
	{
		this->pMovementComponent = new MovementComponent(this->mZombieSprite, max_velocity, acceleration,
			deceleration);
	}

	void Zombies::createAnimationComponent(sf::Texture & texture_sheet)
	{
		this->pAnimationComponent = new AnimationComponent(this->mZombieSprite, texture_sheet);
	}

	bool Zombies::collision(const float & deltaTime)
	{
		if (this->mZombieSprite.getGlobalBounds().intersects(this->pPlayer.getGobalBounds()))
		{
			this->mIsAttacking = true;

			this->attack(deltaTime);
		}

		return false;
	}

	void Zombies::attack(const float & deltaTime)
	{
		if (this->mIsAttacking)
		{
			if (this->mZombieSprite.getScale().x > 0.f) //Facing left
				this->mZombieSprite.setOrigin(96.f, 0.f);

			if (this->pAnimationComponent->play("ATTACK", deltaTime, true))
			{
				this->mIsAttacking = false;

				if (this->mZombieSprite.getScale().x > 0.f) //Facing left
					this->mZombieSprite.setOrigin(0.f, 0.f);

				else //Facing right
					this->mZombieSprite.setOrigin(258.f, 0.f);
			}
		}
	}
}