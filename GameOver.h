//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "GameOverHUD.h"

class GameOver : public World
{
	public:
		GameOver(sf::RenderWindow& window,std::unique_ptr<World>* currentWorld, int levelID, std::vector<const char*>& levels);
		~GameOver();
		virtual void loadResources() override;
		virtual void buildGraph() override;
		TextureHolder textures;
		FontHolder fonts;

	private:
		int levelID = -1;
		GameOverHUD* hud = nullptr;
		std::vector<const char*>* levels;
};

