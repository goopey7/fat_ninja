//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "Ninja.h"
#include "Enemy.h"

class Level : public World
{
	public:
		explicit Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld);
		explicit Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld,const char* fileName);
		~Level();
		virtual void update(const float dt) override;
	protected:
		virtual void loadResources() override;
		virtual void buildGraph() override;
		TextureHolder textures;
		Player sfx;
		SoundHolder soundBuffers;
	private:
		void loadEntitiesFromFile(const char* fileName);
		void loadPlayerFromFile(const char* fileName);

		Ninja* player;
};

