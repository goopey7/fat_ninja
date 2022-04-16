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
		void followMouse();
		void followKbd();
		void stopKbd();
	private:
		sf::RenderWindow* window;
		bool bFollowMouse = false;
		bool bFollowKbd = false;
		float acceleration = 100.f;
};

