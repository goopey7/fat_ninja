//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"
#include "gf/Vector.h"
#include "gf/Line.h"
#include "Resources.h"
#include "GameHUD.h"

class Shuriken : public Actor
{
	public:
		Shuriken(GameHUD* hud,Player& sounds,const TextureHolder& textures, World* world);
		~Shuriken();
		//virtual void updateCurrent(const float dt) override;
		//virtual void fixedUpateCurrent(const float dt) override;
		void setupTarget(sf::Vector2f target);
		virtual void onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt) override;
		virtual void onDynamicVsDynamicEnter(Actor* other) override;
		virtual void fixedUpdateCurrent(const float dt) override;
		bool hasHitWall() const;
		void stopMoving();
		void setIsBeingUsed(bool isUsing);

	protected:

	private:
		float speed = 500.f;
		sf::Vector2f dir;
		bool bHitWall = false;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;

		const float lifeTime = 3.f; // in seconds
		float timeAlive = 0.f;
		bool bIsBeingUsed = false;

		GameHUD* hud = nullptr;
		Actor* hitOther = nullptr;
		sf::Vector2f relativePos;
};

