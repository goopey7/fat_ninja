//Copyright Sam Collier 2022
#pragma once

#include "gf/World.h"
#include "Resources.h"
#include "MainMenuHUD.h"

class MainMenu : public World
{
	public:
		MainMenu(sf::RenderWindow& window);
		void setCurrentLevel(std::unique_ptr<World>* currentLevel);

	protected:
		virtual void loadTextures();
		virtual void buildGraph() override;
		TextureHolder textures;

	private:
		std::unique_ptr<World>* currentLevel;
		sf::RenderWindow* window;
};

