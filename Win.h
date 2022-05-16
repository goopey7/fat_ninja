//Copyright Sam Collier 2022
#pragma once

#include "Pickup.h"
#include "GameHUD.h"

class Win : public Pickup
{
	public:
		Win(Player& sounds, const TextureHolder& textures, World* currentWorld);
		~Win();
		virtual unsigned int getCategory() const override;
};

