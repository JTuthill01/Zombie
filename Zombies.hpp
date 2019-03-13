#pragma once
#include "Level.hpp"
#include "EvilKnights.hpp"

namespace Level
{
	class Zombies :
		public Level
	{
	public:
		Zombies();
		Zombies(sf::RenderWindow* window, std::stack<Level*>* level);
		virtual ~Zombies();

		// Inherited via Level
		virtual void render(sf::RenderTarget * target) override;
		virtual void initTextures() override;
		virtual void update(const float & deltaTime) override;

		void updateAnimations(const float& deltaTime);
		void move(const float direction_x, const float direction_y, const float  & deltaTime);

		//inline sf::FloatRect getGobalBounds()const { return this->mOrcSprite.getGlobalBounds(); }
		//inline sf::Vector2f getPosition() const { return this->mOrcSprite.getPosition(); }

		bool IsAttacking() const { return pIsAttacking; }

	protected:
		MovementComponent* pMovementComponent;
		AnimationComponent* pAnimationComponent;

		float pMovementSpeed;

	private:
		Player mPlayer;

		bool mPlayerPosition;

		sf::Texture mZombieTexture;
		sf::Sprite mZombieSprite;

		sf::Texture mLevelTexture;
		sf::Sprite mLevelSprite;

		virtual void updatePlayerInput(const float & deltaTime) override;
		void updateAttack(const float& deltaTime);
		void createMovementComponent(const float max_velocity,
			const float acceleration, const float deceleration);
		void createAnimationComponent(sf::Texture& texture_sheet);
		void reset(const float& deltaTime);

		bool mIsContact;
		bool mIsAttacking;

		// Inherited via Level
		virtual bool collision(const float & deltaTime) override;
		virtual void attack(const float & deltaTime) override;
	};
}