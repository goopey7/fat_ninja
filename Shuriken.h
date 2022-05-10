//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"
#include "gf/Vector.h"
#include "gf/Line.h"
#include "Resources.h"

class Shuriken : public Actor
{
	public:
		Shuriken(const TextureHolder& textures, World* world);
		~Shuriken();
		//virtual void updateCurrent(const float dt) override;
		//virtual void fixedUpateCurrent(const float dt) override;
		void setupTarget(sf::Vector2f target);
		virtual void onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt) override;
		bool hasHitWall();

	protected:

	private:
		float speed = 500.f;
		sf::Vector2f dir;
		bool bHitWall = false;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

