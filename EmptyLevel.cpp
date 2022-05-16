//Copyright Sam Collier 2022

#include "EmptyLevel.h"

EmptyLevel::EmptyLevel(sf::RenderWindow& window,std::unique_ptr<World>* currentWorld)
	: World(window,currentWorld)
{
	loadTextures();
	buildGraph();
}

void EmptyLevel::loadTextures()
{
	textures.load(Textures::Shuriken,"art/shuriken.png");
}

void EmptyLevel::buildGraph()
{
}

