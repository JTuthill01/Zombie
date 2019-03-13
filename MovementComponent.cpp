#include "stdafx.hpp"
#include "MovementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite& sprite, float max_velocity,
	float acceleration, float deceleration) :
	mSprite(sprite), mMax_Velocity(max_velocity), mAcceleration(acceleration),
	mDeceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f MovementComponent::getVelocity() const
{
	return this->mVelocity;
}

const float & MovementComponent::getMaxVelocity() const
{
	return this->mMax_Velocity;
}

void MovementComponent::move(const float direction_x, const float direction_y,
	const float & deltaTime)
{
	this->mVelocity.x += this->mAcceleration * direction_x;

	this->mVelocity.y += this->mAcceleration * direction_y;
}

void MovementComponent::update(const float & deltaTime)
{
	if (this->mVelocity.x > 0.f)  //Check right
	{
		//Max Velocity Check
		if (this->mVelocity.x > this->mMax_Velocity)
			this->mVelocity.x = this->mMax_Velocity;

		//Deceleration x positive
		this->mVelocity.x -= mDeceleration;
		if (this->mVelocity.x < 0.f)
			this->mVelocity.x = 0.f;
	}

	else if (this->mVelocity.x < 0.f)
	{
		//Max Velocity check x negative
		if (this->mVelocity.x < -this->mMax_Velocity)
			this->mVelocity.x = -this->mMax_Velocity;

		//Deceleration x negative
		this->mVelocity.x += mDeceleration;
		if (this->mVelocity.x > 0.f)
			this->mVelocity.x = 0.f;
	}

	if (this->mVelocity.y > 0.f)  //Check right
	{
		//Max Velocity Check
		if (this->mVelocity.y > this->mMax_Velocity)
			this->mVelocity.y = this->mMax_Velocity;

		//Deceleration y positive
		this->mVelocity.y -= mDeceleration;
		if (this->mVelocity.y < 0.f)
			this->mVelocity.y = 0.f;
	}

	else if (this->mVelocity.y < 0.f)
	{
		//Max Velocity check y negative
		if (this->mVelocity.y < -this->mMax_Velocity)
			this->mVelocity.y = -this->mMax_Velocity;

		this->mVelocity.y += mDeceleration;
		if (this->mVelocity.y > 0.f)
			this->mVelocity.y = 0.f;
	}

	//Final Move
	this->mSprite.move(this->mVelocity * deltaTime);
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->mVelocity.x == 0.f && this->mVelocity.y == 0.f)
			return true;
		break;

	case MOVING:
		if (this->mVelocity.x == 0.f || this->mVelocity.y == 0.f)
			return true;

		break;

	case MOVING_LEFT:
		if (this->mVelocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:
		if (this->mVelocity.x > 0.f)
			return true;

		break;

	case  MOVING_UP:
		if (this->mVelocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:
		if (this->mVelocity.y > 0.f)
			return true;
		break;

	default:
		break;
	}

	return false;
}