//Copyright Sam Collier 2022

#include "Level.h"

Level::Level(sf::RenderWindow& window)
	: World(window)
{
	loadTextures();
	buildGraph();
	loadFromFile("untitled.json", textures);
}

void Level::loadTextures()
{
	// Load Textures Here
	textures.load(Textures::Mario,"art/marioSheet.png");
	textures.load(Textures::Terminal, "art/bkg.jpg");
}

void Level::buildGraph()
{
	// Player Entity
	std::unique_ptr<Mario> mario(new Mario(textures,&window));
	mario->setPosition(sf::Vector2f(600.f,50.f));
	addNode(&mario,Entity,true);

	/*

	// Test Wall
	for(int i=0;i<10;i++)
	{
		std::unique_ptr<Actor> floor(new Actor(textures));
		floor->setTexture(Textures::Brick);
		floor->setPosition(spawnPos+sf::Vector2f(i*16*5+500.f,0.f));
		floor->setTextureRect(sf::IntRect(0,0,16,16));
		floor->setCollisionBox(sf::FloatRect(0,0,16,16));
		floor->scale(5.f, 5.f);
		addNode(&floor,Object,true);

		std::unique_ptr<Actor> wall(new Actor(textures));
		wall->setTexture(Textures::Brick);
		wall->setPosition(spawnPos+sf::Vector2f(16*5*10+500.f,(i)*-16*5));
		wall->setTextureRect(sf::IntRect(0,0,16,16));
		wall->setCollisionBox(sf::FloatRect(0,0,16,16));
		wall->scale(5.f, 5.f);
		addNode(&wall,Object,true);
	}
	*/
	
	// bkg
	std::unique_ptr<SpriteNode> bkg(new SpriteNode(textures.get(Textures::Terminal)));
	bkg->setPosition(0.f,0.f);
	bkg->scale(4.f,4.f);
	addNode(&bkg,Background);
}

