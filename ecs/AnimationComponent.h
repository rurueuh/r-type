#pragma once
#include "Component.h"

struct Animation
{
	sf::Texture* texture = nullptr;
	float switchTime = 0;
	uint16_t frameCount = 0;
	std::vector<sf::IntRect> frames = {};
	std::vector<uint16_t> frameOrder = {};

	void setDoOnceFrames(std::vector<uint16_t> frames)
	{
		this->doOnceFrames.clear();
		for (auto frame : frames)
		{
			this->doOnceFrames.push_back(std::make_pair(frame, false));
		}
	}

	bool operator==(const Animation& other) const
	{
		return this->texture == other.texture &&
			this->switchTime == other.switchTime &&
			this->frameCount == other.frameCount &&
			this->frames == other.frames &&
			this->frameOrder == other.frameOrder;
	}

	std::vector<std::pair<uint16_t, bool>> doOnceFrames = {}; // <frame, hasPlayed>
};

namespace Anim {
	const std::vector<sf::IntRect> IDLE			= { sf::IntRect(17, 143, 30, 47) };
	const std::vector<sf::IntRect> IDLE_LEFT	= {sf::IntRect(23, 79, 20, 47)};
	const std::vector<sf::IntRect> IDLE_RIGHT	= {sf::IntRect(21, 207, 20, 47)};
	const std::vector<sf::IntRect> IDLE_BACK	= {sf::IntRect(17, 16, 30, 46)};
	const std::vector<sf::IntRect> WALK_LEFT = {
		sf::IntRect(83, 592, 25, 46), sf::IntRect(149, 591, 22, 46), sf::IntRect(215, 591, 22, 46), sf::IntRect(278, 591, 24, 47), sf::IntRect(340, 592, 28, 46), sf::IntRect(407, 591, 23, 47), sf::IntRect(471, 591, 22, 47), sf::IntRect(535, 591, 21, 47)
	};
	const std::vector<sf::IntRect> WALK_RIGHT = {
		sf::IntRect(83, 720, 25, 46), sf::IntRect(149, 719, 22, 46), sf::IntRect(215, 719, 22, 46), sf::IntRect(278, 719, 24, 47), sf::IntRect(340, 720, 28, 46), sf::IntRect(407, 719, 23, 47), sf::IntRect(471, 719, 22, 47), sf::IntRect(535, 719, 21, 47)
	};
	const std::vector<sf::IntRect> WALK = {
		sf::IntRect(81, 655, 30, 47), sf::IntRect(145, 655, 30, 48), sf::IntRect(210, 656, 29, 47), sf::IntRect(273, 655, 30, 48), sf::IntRect(337, 655, 30, 47), sf::IntRect(401, 655, 30, 48), sf::IntRect(465, 656, 29, 47), sf::IntRect(529, 655, 30, 48)
	};
	const std::vector<sf::IntRect> WALK_BACK = {
		sf::IntRect(81, 527, 30, 46), sf::IntRect(145, 527, 30, 47), sf::IntRect(209, 528, 29, 47), sf::IntRect(273, 527, 30, 47), sf::IntRect(337, 527, 30, 46), sf::IntRect(401, 527, 30, 47), sf::IntRect(466, 528, 29, 47), sf::IntRect(529, 527, 30, 47)
	};
}

class AnimationComponent :
    public Component
{
    public:
		AnimationComponent(Entity *entity) : Component(entity, true, true), m_sprite(entity->getSprite()) {};
		~AnimationComponent() {};

		void update(float dt) override;
		void draw(sf::RenderTarget& window) override;

		void createAnimation(std::string key, sf::Texture* texture, float switchTime, uint16_t frameCount, std::vector<uint16_t> frameOrder, std::vector<sf::IntRect> frame);
		void createAnimation(std::string key, struct Animation animation);

		void playAnimation(std::string key, bool loop = false);
		bool isPlaying() const { return m_isPlaying; }
		void pauseAnimation() { m_isPlaying = false; }
		void resumeAnimation() { m_isPlaying = true; }
		void stopAnimation() { m_isPlaying = false; m_currentFrame = 0; }
		void setLooping(bool loop) { m_isLooping = loop; }
		bool isLooping() const { return m_isLooping; }
	private:
		sf::Clock m_clock;
		sf::Sprite& m_sprite;
		std::map<std::string, struct Animation> m_animations = {};
		struct Animation* m_currentAnimation = nullptr;
		uint16_t m_currentFrame = 0;
		bool m_isPlaying = false;
		bool m_isLooping = false;
};

