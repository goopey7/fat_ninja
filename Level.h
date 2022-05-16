//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "Ninja.h"
#include "Enemy.h"
#include "GameHUD.h"
#include "Win.h"

class Level : public World
{
	public:
		explicit Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld);
		explicit Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld,const char* fileName);
		~Level();
		virtual void update(const float dt) override;
		virtual void buildGraph() override;
	protected:
		virtual void loadResources() override;
		TextureHolder textures;
		FontHolder fonts;
		Player sfx;
		SoundHolder soundBuffers;
		void addSfx(Sfx::ID id, const char* fileName);
	private:
		void loadEntitiesFromFile(const char* fileName);
		void loadPlayerFromFile(const char* fileName);

		Ninja* player;
		GameHUD* hud;
};

