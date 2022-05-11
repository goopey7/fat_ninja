//Copyright Sam Collier 2022

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window, std::unique_ptr<World>* currentLevel)
	: World(window), window(&window), currentLevel(currentLevel)
{
	loadTextures();
	buildGraph();
	viewScale = 1.f;
	/*
	float viewScale = 1.f;
	sf::FloatRect windowRect(0.f,0.f,window.getSize().x*viewScale,window.getSize().y*viewScale);
	window.setView(sf::View(windowRect));
	*/

	std::cout << "MAIN MENU LEVEL\n";
	std::cout << this->currentLevel << std::endl;
	std::unique_ptr<MainMenuHUD> menu(new MainMenuHUD(&window,currentLevel));
	addNode(&menu,HUD);
}

void MainMenu::loadTextures()
{
}

void MainMenu::buildGraph()
{
	
}
