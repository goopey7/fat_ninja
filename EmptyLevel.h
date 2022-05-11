//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "Mario.h"

class EmptyLevel : public World
{
	public:
		explicit EmptyLevel(sf::RenderWindow& window);
	protected:
		virtual void loadTextures();
		virtual void buildGraph() override;
		TextureHolder textures;
};

