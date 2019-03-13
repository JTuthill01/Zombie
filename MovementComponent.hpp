#pragma once

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN, ATTACK };

class MovementComponent
{
public:
	MovementComponent(sf::Sprite& sprite, float max_velocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//SFML Accessors
	const sf::Vector2f getVelocity() const;

	//Accessors
	const float& getMaxVelocity() const;

	void move(const float x, const float y, const float& deltaTime);
	void update(const float& deltaTime);

	//Booleans
	const bool getState(const short unsigned state) const;

private:
	//Variables
	float mMax_Velocity;
	float mAcceleration;
	float mDeceleration;

	//SFML Stuff
	sf::Vector2f mVelocity;
	sf::Sprite& mSprite;
};