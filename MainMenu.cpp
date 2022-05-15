//Copyright Sam Collier 2022

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld)
	: Level(window,currentWorld), window(&window) 
{
	viewScale = 1.f;
	loadResources();
	buildGraph();
}

MainMenu::MainMenu(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld,const char* fileName)
	: Level(window,currentWorld,fileName), window(&window)
{
	viewScale = 1.f;
	loadResources();
	buildGraph();
}

void MainMenu::loadResources()
{
	fonts.load(Fonts::Arial,"font/arial.ttf");
	fonts.load(Fonts::Pixel,"font/bit01.ttf");
}

void MainMenu::buildGraph()
{
	std::unique_ptr<MainMenuHUD> menu(new MainMenuHUD(fonts,window,currentWorld));
	addNode(&menu,HUD);
}

