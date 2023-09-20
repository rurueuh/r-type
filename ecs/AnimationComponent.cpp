#include "AnimationComponent.h"

void AnimationComponent::update(float dt)
{
}

void AnimationComponent::draw(sf::RenderTarget& window)
{
	if (this->m_isPlaying)
	{
		static int saveRecursive = 0;
		if (this->m_clock.getElapsedTime().asSeconds() >= this->m_currentAnimation->switchTime)
		{
			this->m_currentFrame++;
			
			
			if (this->m_currentFrame >= this->m_currentAnimation->frameCount)
			{
				if (this->m_isLooping)
				{
					this->m_currentFrame = 0;
				}
				else
				{
					this->m_isPlaying = false;
					return;
				}
			}
			for (auto& onceFrame : this->m_currentAnimation->doOnceFrames)
			{
				if (this->m_currentFrame == onceFrame.first)
				{
					if (onceFrame.second == true) {
						if (saveRecursive > this->m_currentAnimation->frameCount) // if the animation has a recursive loop, it will be detected here
						{
							std::string name = "unknow";
							for (auto& anim : this->m_animations)
							{
								if (anim.second == *this->m_currentAnimation)
								{
									name = anim.first;
									break;
								}
							}
							std::cout << "AnimationComponent::draw: Animation " << name << " has a recursive loop" << std::endl;
							return;
						}
						saveRecursive++;
						draw(window);
					}
					else {
						onceFrame.second = !onceFrame.second;
					}
					break;
				}
			}
			saveRecursive = 0;
			this->m_sprite.setTextureRect(this->m_currentAnimation->frames[this->m_currentAnimation->frameOrder[this->m_currentFrame]]);
			this->m_clock.restart();
		}
	}
}

void AnimationComponent::createAnimation(std::string key, sf::Texture* texture, float switchTime, uint16_t frameCount, std::vector<uint16_t> frameOrder, std::vector<sf::IntRect> frame)
{
	if (this->m_animations.find(key) != this->m_animations.end())
	{
		std::cout << "AnimationComponent::createAnimation: Animation " << key << " already exists" << std::endl;
		return;
	}

	Animation animation{
		.texture = texture,
		.switchTime = switchTime,
		.frameCount = frameCount,
		.frameOrder = frameOrder,
	};
	animation.frames = frame;
	this->m_animations[key] = animation;
}

void AnimationComponent::createAnimation(std::string key, Animation animation)
{
	if (this->m_animations.find(key) != this->m_animations.end())
	{
		std::cout << "AnimationComponent::createAnimation: Animation " << key << " already exists" << std::endl;
		return;
	}
	this->m_animations[key] = animation;
}

void AnimationComponent::playAnimation(std::string key, bool loop)
{
	if (this->m_animations.find(key) == this->m_animations.end())
	{
		std::cout << "AnimationComponent::playAnimation: Animation " << key << " not found" << std::endl;
		return;
	}
	if (this->m_currentAnimation == &this->m_animations[key])
	{
		return;
	}
	this->m_currentAnimation = &this->m_animations[key];
	this->m_currentFrame = 0;
	this->m_isPlaying = true;
	this->m_isLooping = loop;
	this->m_clock.restart();
	this->m_sprite.setTextureRect(this->m_currentAnimation->frames[this->m_currentAnimation->frameOrder[this->m_currentFrame]]);
}
