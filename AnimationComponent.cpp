#include "stdafx.hpp"
#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(sf::Sprite & sprite, sf::Texture & texture_sheet) :
	mSprite(sprite), mTextureSheet(texture_sheet), mLastAnimation(nullptr), mPriorityAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto &it : this->animations)
		delete it.second;
}

void AnimationComponent::addAnimation(const std::string key, float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(this->mSprite, this->mTextureSheet, animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float & deltaTime, const bool isPriority)
{
	if (this->mPriorityAnimation)
	{
		if (this->mPriorityAnimation == this->animations[key])
		{
			if (this->mLastAnimation != this->animations[key])
			{
				if (this->mLastAnimation == nullptr)
					this->mLastAnimation = this->animations[key];

				else
				{
					this->mLastAnimation->reset();
					this->mLastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(deltaTime))
				this->mPriorityAnimation = nullptr;
		}
	}

	else
	{
		if (isPriority)
			this->mPriorityAnimation = this->animations[key];

		if (this->mLastAnimation != this->animations[key])
		{
			if (this->mLastAnimation == nullptr)
				this->mLastAnimation = this->animations[key];

			else
			{
				this->mLastAnimation->reset();
				this->mLastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(deltaTime);
	}

	return this->animations[key]->done();
}

const bool& AnimationComponent::play(const std::string key, const float & deltaTime,
	const float & modifier, const float & modifier_max, const bool isPriority)
{
	if (this->mPriorityAnimation)
	{
		if (this->mPriorityAnimation == this->animations[key])
		{
			if (this->mLastAnimation != this->animations[key])
			{
				if (this->mLastAnimation == nullptr)
					this->mLastAnimation = this->animations[key];

				else
				{
					this->mLastAnimation->reset();
					this->mLastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(deltaTime, abs(modifier / modifier_max)))
				this->mPriorityAnimation = nullptr;
		}
	}

	else
	{
		if (isPriority)
			this->mPriorityAnimation = this->animations[key];

		if (this->mLastAnimation != this->animations[key])
		{
			if (this->mLastAnimation == nullptr)
				this->mLastAnimation = this->animations[key];

			else
			{
				this->mLastAnimation->reset();
				this->mLastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(deltaTime, abs(modifier / modifier_max));
	}

	return this->animations[key]->done();
}

const bool & AnimationComponent::done(const std::string key)
{
	return this->animations[key]->done();
}