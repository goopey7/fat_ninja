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
	std::unique_ptr<Shuriken> shuriken(new Shuriken(textures,this));
	shuriken->setTexture(Textures::Shuriken);
	sf::Vector2u textureSize = shuriken->getTextureSize();
	shuriken->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
	shuriken->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
	shuriken->setPosition(0.f,0.f);
	shuriken->setIsDynamic(true);
	addNode(&shuriken,Tile);
}

