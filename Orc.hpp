#pragma once
#include "Level.hpp"
#include "Zombies.hpp"

namespace Level
{
	class Orc :
		public Level
	{
	public:
		Orc();
		Orc(sf::RenderWindow* window, std::stack<Level*>* level);
		virtual ~Orc();

		// Inherited via Level
		virtual void render(sf::RenderTarget * target) override;
		virtual void initTextures() override;
		virtual void update(const float & deltaTime) override;

		void updateAnimations(const float& deltaTime);
		void move(const float direction_x, const float direction_y, const float  & deltaTime);

		inline sf::FloatRect getGobalBounds()const { return this->mOrcSprite.getGlobalBounds(); }
		inline sf::Vector2f getPosition() const { return this->mOrcSprite.getPosition(); }

		bool IsAttacking() const { return mIsAttacking; }

	protected:
		MovementComponent* pMovementComponent;
		AnimationComponent* pAnimationComponent;

		float pMovementSpeed;

	private:
		sf::Texture mOrcTexture;
		sf::Sprite mOrcSprite;

		sf::Texture mLeveltexture;
		sf::Sprite mLevelSprite;

		void updateAttack();
		void createMovementComponent(const float max_velocity,
			const float acceleration, const float deceleration);
		void createAnimationComponent(sf::Texture& texture_sheet);

		bool mIsContact;
		bool mIsAttacking;

	};
}
