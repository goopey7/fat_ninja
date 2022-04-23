//Copyright Sam Collier 2022

#include "Level.h"

Level::Level(sf::RenderWindow& window)
	: World(window)
{
	loadFromFile("test.json",textures,Textures::Size);
	loadTextures();
	buildGraph();
}

void Level::loadTextures()
{
	// Load Textures Here
	textures.load(Textures::Mario,"art/marioSheet.png");
}

void Level::buildGraph()
{
	std::unique_ptr<Mario> mario(new Mario(textures,&window));
	mario->setTexture(Textures::Mario);
	sf::Vector2u textureSize = mario->getTextureSize();
	mario->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
	mario->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
	mario->setPosition(0.f,-30.f);
	mario->setIsDynamic(true);
	addNode(&mario,Tile);
}

