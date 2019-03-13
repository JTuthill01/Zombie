#pragma once
#include "Player.hpp"

namespace Level
{
	class Level
	{
	public:
		Level(sf::RenderWindow* window, std::stack<Level*>* level);
		~Level();

		virtual bool collision(const float& deltaTime) = 0;
		virtual void attack(const float& deltaTime) = 0;
		virtual void updatePlayerInput(const float & deltaTime) = 0;
		virtual void update(const float& deltaTime) = 0;
		virtual void render(sf::RenderTarget* target) = 0;
		virtual void initTextures() = 0;
		virtual void updateAnimations(const float& deltaTime) = 0;
		virtual void move(const float direction_x, const float direction_y, const float  & deltaTime) = 0;
		virtual void createMovementComponent(const float max_velocity,
			const float acceleration, const float deceleration) = 0;
		virtual void createAnimationComponent(sf::Texture& texture_sheet) = 0;

	protected:
		sf::RenderWindow* pWindow;

		Player pPlayer;

		std::stack <Level*>* pLevel;

		MovementComponent* pMovementComponent;
		AnimationComponent* pAnimationComponent;

		float pMovementSpeed;

		bool pIsWalking;
		bool pIsAttacking;
	};
}