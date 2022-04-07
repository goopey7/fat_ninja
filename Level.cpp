//Copyright Sam Collier 2022

#include "Level.h"

Level::Level(sf::RenderWindow& window)
	: World(window)
{
	loadTextures();
	buildGraph();
}

void Level::loadTextures()
{
	// Load Textures Here
	textures.load(Textures::Box,"box.jpeg");
	textures.load(Textures::Bkg, "bkg.jpg");
}

void Level::buildGraph()
{
	// RECTANGLE
	std::unique_ptr<Box> box(new Box(textures,&window));
	box->setTexture(Textures::Box);
	sf::Vector2u textureSize = box->getTextureSize();
	box->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
	box->setPosition(300.f,700.f);
	box->followMouse();
	box->followKbd();
	box->toggleDebugMode();
	addNode(&box,Entity,true,true);

	std::unique_ptr<Box> box2(new Box(textures,&window));
	box2->setTexture(Textures::Bkg);
	box2->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
	box2->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
	box2->setPosition(1000.f,600.f);
	box2->toggleDebugMode();
	addNode(&box2,Entity,true);
}

