//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "MainMenuHUD.h"

class MainMenu : public World
{
	public:
		MainMenu(sf::RenderWindow& window, std::unique_ptr<World>* currentLevel);

	protected:
		virtual void loadResources() override;
		virtual void buildGraph() override;
		TextureHolder textures;
		FontHolder fonts;

	private:
		sf::RenderWindow* window;
};

