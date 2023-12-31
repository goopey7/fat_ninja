//Copyright Sam Collier 2022
#pragma once

#include "Level.h"
#include "Resources.h"
#include "MainMenuHUD.h"

class MainMenu : public Level
{
	public:
		MainMenu(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld);
		MainMenu(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld,const char* fileName);
		virtual void buildGraph() override;
	protected:
		virtual void loadResources() override;
		TextureHolder textures;
		FontHolder fonts;

	private:
		sf::RenderWindow* window;
};

