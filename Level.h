//Copyright Sam Collier 2022
#pragma once

#include "goopFramework/World.h"
#include "Resources.h"
#include "Tux.h"

class Level : public World
{
	public:
		explicit Level(sf::RenderWindow& window);
	protected:
		void loadTextures();
		virtual void buildGraph() override;
		TextureHolder textures;
};

