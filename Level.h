//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "Mario.h"
#include "Enemy.h"
#include "MainMenu.h"

class Level : public World
{
	public:
		explicit Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld);
		explicit Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld,const char* fileName);
		virtual void update(const float dt) override;
	protected:
		virtual void loadResources() override;
		virtual void buildGraph() override;
		TextureHolder textures;
	private:
		void loadEntitiesFromFile(const char* fileName);

		Mario* player;
};

