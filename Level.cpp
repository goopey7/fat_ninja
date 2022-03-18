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
	std::unique_ptr<Node> mario(new Mario(textures,&window));
	mario->setPosition(spawnPos);
	addNode(mario,Entity,true);

	// Test Wall
	for(int i=0;i<10;i++)
	{
		std::unique_ptr<Node> floorNode(new Actor(textures));
		Actor* floor = reinterpret_cast<Actor*>(floorNode.get());
		floor->setTexture(Textures::Brick);
		floor->setPosition(spawnPos+sf::Vector2f(i*16*5+500.f,0.f));
		floor->setTextureRect(sf::IntRect(0,0,16,16));
		floor->setCollisionBox(sf::FloatRect(0,0,16,16));
		floor->scale(5.f, 5.f);
		addNode(floorNode,Object,true);

		std::unique_ptr<Node> wallNode(new Actor(textures));
		Actor* wall = reinterpret_cast<Actor*>(wallNode.get());
		wall->setTexture(Textures::Brick);
		wall->setPosition(spawnPos+sf::Vector2f(16*5*10+500.f,(i)*-16*5));
		wall->setTextureRect(sf::IntRect(0,0,16,16));
		wall->setCollisionBox(sf::FloatRect(0,0,16,16));
		wall->scale(5.f, 5.f);
		addNode(wallNode,Object,true);
	}
	
	// bkg
	std::unique_ptr<Node> bkg(new SpriteNode(textures.get(Textures::Terminal)));
	bkg->setPosition(0.f,0.f);
	bkg->scale(4.f,4.f);
	addNode(bkg,Background);
}

