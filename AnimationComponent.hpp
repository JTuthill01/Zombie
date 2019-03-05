#pragma once

class AnimationComponent
{
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key, float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	const bool& play(const std::string key, const float& deltaTime, const bool isPriority = false);
	const bool& play(const std::string key, const float& deltaTime, const float& modifier,
		const float& modifier_max, const bool isPriority = false);

	const bool& done(const std::string key);
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& mSprite;
		sf::Texture& mTextureSheet;
		sf::IntRect mStartRect;
		sf::IntRect mCurrentRect;
		sf::IntRect mEndRect;

		float animationTimer;
		float timer;
		int width;
		int height;

		bool isDone;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
			float animation_timer,
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: mSprite(sprite), mTextureSheet(texture_sheet),
			animationTimer(animation_timer), width(width), height(height), isDone(false)
		{
			this->timer = 0.f;
			this->mStartRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->mCurrentRect = this->mStartRect;
			this->mEndRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->mSprite.setTexture(this->mTextureSheet, true);
			this->mSprite.setTextureRect(this->mStartRect);
		}

		const bool& done() const { return this->isDone; }

		//Functions
		const bool& play(const float& deltaTime)
		{
			//Update timer
			this->isDone = false;
			this->timer += 100.f * deltaTime;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				//Animate
				if (this->mCurrentRect != this->mEndRect)
					this->mCurrentRect.left += this->width;

				else //Reset
				{
					this->mCurrentRect.left = this->mStartRect.left;
					this->isDone = true;
				}
				this->mSprite.setTextureRect(this->mCurrentRect);
			}
			return this->isDone;
		}

		const bool& play(const float& deltaTime, float modifier_percent)
		{
			//Update timer
			if (modifier_percent < 0.5f)
				modifier_percent = 0.5f;

			this->timer += modifier_percent * 100.f * deltaTime;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->isDone = false;
				this->timer = 0.f;

				//Animate
				if (this->mCurrentRect != this->mEndRect)
					this->mCurrentRect.left += this->width;

				else //Reset
				{
					this->mCurrentRect.left = this->mStartRect.left;
					this->isDone = true;
				}
				this->mSprite.setTextureRect(this->mCurrentRect);
			}
			return this->isDone;
		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->mCurrentRect = this->mStartRect;
		}
	};

	sf::Sprite& mSprite;
	sf::Texture& mTextureSheet;

	Animation* mLastAnimation;
	Animation* mPriorityAnimation;
	std::map<std::string, Animation*> animations;
};