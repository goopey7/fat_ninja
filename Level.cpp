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
	box->setPosition(window.getSize().x/2.f,window.getSize().y/2.f);
	addNode(&box,Entity,true);

	// MOUSE CONTROLLED RECTANGLE
	/*
	std::unique_ptr<Box> mBox(new Box(textures,&window));
	mBox->setTexture(Textures::Box);
	textureSize = mBox->getTextureSize();
	mBox->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
	mBox->followMouse();
	mBox->setOrigin(100.f,100.f);
	addNode(&mBox,Entity,true);
	*/

	// bkg
	std::unique_ptr<SpriteNode> bkg(new SpriteNode(textures.get(Textures::Bkg)));
	addNode(&bkg,Background);
	
}

