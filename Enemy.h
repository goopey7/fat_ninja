//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"
#include "Shuriken.h"
#include "gf/Animation.h"
#include "Resources.h"
#include "gf/Collision.h"
#include "Mario.h"

class Enemy : public Actor
{
	public:
		Enemy(const TextureHolder& textures, World* currentWorld, Mario* player);
		~Enemy();
		void handleAnimations(const float dt);
		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpdateCurrent(const float dt) override;
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

		float gravity = 98.1f*6.f;
		sf::Vector2f dir = {1.f,0.f};
		float speed = 22.f;

		float rangeOfSight = 100.f;

		Mario* player;
};
