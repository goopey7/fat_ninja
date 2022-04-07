//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"
#include "gf/Collision.h"

class Box : public Actor
{
	public:
		Box(const TextureHolder& textures, sf::RenderWindow* window);
		virtual void updateCurrent(const float dt) override;
		virtual unsigned int getCategory() const override;
		virtual void onCollision() override;
		virtual void onCollisionExit() override;
		void followMouse();
		void followKbd();
	private:
		sf::RenderWindow* window;
		bool bFollowMouse = false;
		bool bFollowKbd = false;
		float speed = 100.f;
};

