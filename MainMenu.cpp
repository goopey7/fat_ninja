//Copyright Sam Collier 2022

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window)
	: World(window), window(&window)
{
	loadTextures();
	buildGraph();
}

void MainMenu::loadTextures()
{
}

void MainMenu::buildGraph()
{
	
}

void MainMenu::setCurrentLevel(std::unique_ptr<World>* currentLevel)
{
	this->currentLevel = currentLevel;
	std::cout << "MAIN MENU LEVEL\n";
	std::cout << this->currentLevel << std::endl;
	std::unique_ptr<MainMenuHUD> menu(new MainMenuHUD(window,currentLevel));
	addNode(&menu,HUD);
}

