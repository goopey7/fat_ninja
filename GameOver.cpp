//Copyright Sam Collier 2022

#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow& window,std::unique_ptr<World>* currentWorld, int levelID, std::vector<const char*>& levels)
	: World(window,currentWorld), levelID(levelID), levels(&levels)
{
	loadResources();
	buildGraph();
	viewScale = 1.f;
}

void GameOver::loadResources()
{
	fonts.load(Fonts::Pixel,"font/bit01.ttf");
	fonts.load(Fonts::Arial,"font/arial.ttf");
}

void GameOver::buildGraph()
{
	std::unique_ptr<GameOverHUD> hud(new GameOverHUD(fonts,window,bComplete));
	this->hud = hud.get();
	addNode(&hud,HUD);
}

GameOver::~GameOver()
{
}

