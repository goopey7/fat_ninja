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
	textures.load(Textures::Mario,"art/marioSheet.png");
	textures.load(Textures::Terminal, "art/bkg.jpg");
	textures.load(Textures::Brick,"art/bricks.png");
}

void Level::buildGraph()
{
	// Player Entity
	std::unique_ptr<Mario> mario(new Mario(textures,&window));
	mario->setPosition(spawnPos);
	collidingActors.push_back(mario.get());
	worldLayers[Entity]->attachChild(std::move(mario));

	// Test Wall
	std::unique_ptr<Actor> wall(new Actor(textures));
	wall->setTexture(Textures::Brick);
	wall->setPosition(spawnPos+sf::Vector2f(500.f,0.f));
	wall->setTextureRect(sf::IntRect(0,0,16,16));
	wall->setScale(5.f, 5.f);
	wall->setCollisionBox(sf::FloatRect(0,0,16,16));
	collidingActors.push_back(wall.get());
	worldLayers[Object]->attachChild(std::move(wall));

	// bkg
	std::unique_ptr<SpriteNode> bkg(new SpriteNode(textures.get(Textures::Terminal)));
	bkg->setPosition(0.f,0.f);
	bkg->scale(4.f,4.f);
	worldLayers[Background]->attachChild(std::move(bkg));
}

