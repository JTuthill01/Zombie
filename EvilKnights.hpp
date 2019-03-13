#pragma once
#include "Level.hpp"

namespace Level
{
	class EvilKnights :
		public Level
	{
	public:
		EvilKnights();

		EvilKnights(sf::RenderWindow* window, std::stack<Level*>* level);
		virtual ~EvilKnights();

		// Inherited via Level
		virtual void updatePlayerInput(const float & deltaTime) override;
		virtual void update(const float & deltaTime) override;
		virtual void render(sf::RenderTarget * target) override;
		virtual void initTextures() override;
		virtual void updateAnimations(const float & deltaTime) override;
		virtual void move(const float direction_x, const float direction_y, const float & deltaTime) override;
		virtual void createMovementComponent(const float max_velocity, const float acceleration, const float deceleration) override;
		virtual void createAnimationComponent(sf::Texture & texture_sheet) override;

	private:
		sf::Texture mKnightTexture;
		sf::Sprite mKnightSprite;

		sf::Texture mLevelTexture;
		sf::Sprite mLevelSprite;

		// Inherited via Level
		virtual void attack(const float & deltaTime) override;
		virtual bool collision(const float & deltaTime) override;

		bool mIsAttacking;
	};
}