#pragma once
#include "AnimationComponent.hpp"
#include "MovementComponent.hpp"

class Player
{
public:
	Player();
	~Player();

	void render(sf::RenderTarget* target);
	void update(const float& deltaTime);
	void updateAnimations(const float& deltaTime);
	void move(const float direction_x, const float direction_y, const float  & deltaTime);

	inline sf::FloatRect getGobalBounds()const { return this->mPlayerSprite.getGlobalBounds(); }
	inline sf::Vector2f getPosition() const { return this->mPlayerSprite.getPosition(); }
	inline void setPosition(sf::Vector2f position) { this->mPlayerSprite.setPosition(position); }

	bool IsAttacking() const { return mIsAttacking; }
	bool isLoadLevel() { return this->mLoadLevel;}
	void setLoadLevel(bool TF) { this->mLoadLevel = TF; }

	MovementComponent* pMovementComponent;
	AnimationComponent* pAnimationComponent;

protected:
	

	float pMovementSpeed;

private:
	sf::Texture mPlayerTexture;
	sf::Sprite mPlayerSprite;

	bool mLoadLevel;

	void initTextures();
	void updateAttack();
	void createMovementComponent(const float max_velocity,
		const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	bool mIsContact;
	bool mIsAttacking;
};