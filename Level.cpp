//Copyright Sam Collier 2022

#include "Level.h"

Level::Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld)
	: World(window,currentWorld)
{
	loadResources();
	viewScale = .15f;
}

Level::Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld,const char* fileName)
	: World(window,currentWorld)
{
	loadResources();
	loadFromFile(fileName,textures,Textures::Size);
	loadPlayerFromFile(fileName);
	loadEntitiesFromFile(fileName);
}

void Level::loadResources()
{
	// Manually Load Textures Here
	textures.load(Textures::Mario,"art/marioSheet.png");
	textures.load(Textures::Shuriken,"art/shuriken.png");
}

void Level::update(const float dt)
{
	World::update(dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		currentWorld->reset(new MainMenu(window,currentWorld));
	}
}

void Level::loadEntitiesFromFile(const char* fileName)
{
	using nlohmann::json;
	std::ifstream file(fileName);
	json map = json::parse(file);
	json layers = map["layers"];
	for(json layer : layers)
	{
		if(!layer["objects"].is_null())
		{
			for(json object : layer["objects"])
			{
				if(object["properties"].at(0)["name"] == "entity")
				{
					if(object["properties"].at(0)["value"] == "enemy")
					{
						std::unique_ptr<Enemy> enemy(new Enemy(textures,this,player));
						enemy->setTexture(Textures::Mario);
						sf::Vector2u textureSize = enemy->getTextureSize();
						enemy->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
						enemy->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
						enemy->setPosition((float)object["x"] - textureSize.x/2.f,(float)object["y"] - textureSize.y);
						enemy->setIsDynamic(true);
						addNode(&enemy,Entity);
					}
				}
			}
		}
	}
}

void Level::loadPlayerFromFile(const char* fileName)
{
	using nlohmann::json;
	std::ifstream file(fileName);
	json map = json::parse(file);
	json layers = map["layers"];
	for(json layer : layers)
	{
		if(!layer["objects"].is_null())
		{
			for(json object : layer["objects"])
			{
				if(object["properties"].at(0)["name"] == "entity")
				{
					if(object["properties"].at(0)["value"] == "player")
					{
						std::unique_ptr<Mario> mario(new Mario(textures,this,&window));
						mario->setTexture(Textures::Mario);
						sf::Vector2u textureSize = mario->getTextureSize();
						mario->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
						mario->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
						mario->setPosition((float)object["x"] - textureSize.x/2.f,(float)object["y"] - textureSize.y);
						mario->setIsDynamic(true);
						player = mario.get();
						addNode(&mario,Entity);
					}
				}
			}
		}
	}
}

