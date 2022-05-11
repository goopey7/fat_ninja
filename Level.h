//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "Mario.h"

class Level : public World
{
	public:
		explicit Level(sf::RenderWindow& window);
		explicit Level(sf::RenderWindow& window, const char* fileName);
	protected:
		virtual void loadTextures();
		virtual void buildGraph() override;
		TextureHolder textures;
};

