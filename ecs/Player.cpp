#include "Player.h"

Player::Player() : Entity(sf::Vector2f(100, 100))
{
	this->m_texture = TextureManager::getTexture("assets/player.png");
	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setPosition(sf::Vector2f(100, 100));

	this->initAnimations();
	this->addComponent<ControllerMouvement>();
}

void Player::initAnimations()
{
	std::vector<std::tuple<std::string, float, std::vector<sf::IntRect>, std::vector<uint16_t>>> animations = {
		{"idle"		, 0.f, Anim::IDLE		, {}},
		{"idleRight", 0.f, Anim::IDLE_RIGHT	, {}},
		{"idleLeft" , 0.f, Anim::IDLE_LEFT  , {}},
		{"idleBack" , 0.f, Anim::IDLE_BACK  , {}},
		{"walk"		, 0.1f, Anim::WALK		, {}},
		{"walkRight", 0.1f, Anim::WALK_RIGHT, {}},
		{"walkLeft" , 0.1f, Anim::WALK_LEFT	, {}},
		{"walkBack" , 0.1f, Anim::WALK_BACK	, {}},
	};
	this->addComponent<AnimationComponent>();
	auto animCompenant = this->getComponent<AnimationComponent>();
	for (auto& anim : animations) {
		Animation testAnim;
		testAnim.texture = &this->m_texture;
		testAnim.switchTime = std::get<1>(anim);
		testAnim.frameCount = static_cast<uint16_t>(std::get<2>(anim).size());
		for (int i = 0; i < std::get<2>(anim).size(); i++) {
			testAnim.frameOrder.push_back(i);
		}
		testAnim.frames = std::get<2>(anim);
		testAnim.setDoOnceFrames(std::get<3>(anim));
		animCompenant->createAnimation(std::get<0>(anim), testAnim);
	}
	animCompenant->playAnimation("walk", false);
}

Player::~Player()
{
}

void Player::update(float dt)
{
}

void Player::draw(sf::RenderTarget& window)
{
	window.draw(this->m_sprite);
}