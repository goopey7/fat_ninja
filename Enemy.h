//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"
#include "Shuriken.h"
#include "gf/Animation.h"
#include "Resources.h"

class Enemy : public Actor
{
	public:
		Enemy(const TextureHolder& textures, World* currentWorld);
		~Enemy();
		void handleAnimations(const float dt);
		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpdateCurrent(const float dt) override;
		virtual unsigned int getCategory() const override;
		virtual void onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
		virtual void onDynamicVsDynamicEnter(Actor* other) override;

	protected:

	private:
		Animation walk;
		int walkWidth = 15;
		int walkHeight = 21;
		int walkFrames = 4;
		float walkSpeed = 0.1f;
};

