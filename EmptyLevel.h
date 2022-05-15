//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "Ninja.h"

class EmptyLevel : public World
{
	public:
		explicit EmptyLevel(sf::RenderWindow& window,std::unique_ptr<World>* currentWorld);
	protected:
		virtual void loadTextures();
		virtual void buildGraph() override;
		TextureHolder textures;
		Player sfx;
};

