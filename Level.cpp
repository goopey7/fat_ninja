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
	textures.load(Textures::Tux, "art/tux.png");
	textures.load(Textures::Terminal, "art/bkg.jpg");
}

void Level::buildGraph()
{
	// Tux Entity
	std::unique_ptr<Tux> tux(new Tux(textures));
	tux->setPosition(spawnPos);
	worldLayers[Foreground]->attachChild(std::move(tux));

	// bkg
	std::unique_ptr<SpriteNode> bkg(new SpriteNode(textures.get(Textures::Terminal)));
	bkg->setPosition(0.f,0.f);
	bkg->scale(4.f,4.f);
	worldLayers[Background]->attachChild(std::move(bkg));
}

