//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"

class Pickup : public Actor
{
	public:
		Pickup(Player& sounds, const TextureHolder& textures, World* currentWorld);
		~Pickup();

		virtual unsigned int getCategory() const override;

		virtual void onDynamicVsDynamicEnter(Actor* other) override;
		virtual void onPickup();

	protected:

	private:
		sf::Vector2u textureSize = {8,8};
		
};

