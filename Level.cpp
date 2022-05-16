//Copyright Sam Collier 2022

#include "Level.h"

Level::Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld)
	: World(window,currentWorld)
{
	loadResources();
}

Level::Level(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld,const char* fileName)
	: World(window,currentWorld)
{
	loadResources();
	loadFromFile(fileName,sfx,textures,Textures::Size);
	loadPlayerFromFile(fileName);
	loadEntitiesFromFile(fileName);
	song.setLoop(true);
}

void Level::addSfx(Sfx::ID id, const char* fileName)
{
	soundBuffers.load(id,fileName);
	std::unique_ptr<sf::Sound> s(new sf::Sound());
	s->setBuffer(soundBuffers.get(id));
	sfx.add(id,std::move(s));
}

void Level::loadResources()
{
	// Manually Load Resources Here
	textures.load(Textures::Ninja, "art/marioSheetNew.png");
	textures.load(Textures::Shuriken,"art/shuriken.png");
	textures.load(Textures::Enemy,"art/enemyScaled.png");
	textures.load(Textures::Bullet,"art/flatBullet.png");

	fonts.load(Fonts::Arial,"font/arial.ttf");
	fonts.load(Fonts::Pixel,"font/bit01.ttf");

	addSfx(Sfx::Grapple,"sfx/grapple.ogg");
	addSfx(Sfx::Death,"sfx/villager.wav");

	song.openFromFile("music/Mixdown.wav");
}
void Level::buildGraph()
{
	std::unique_ptr<GameHUD> hud(new GameHUD(fonts,window));
	addNode(&hud,HUD);
}

void Level::update(const float dt)
{
	// this way Level's children don't have to hear the first moment of Level's song
	if(song.getStatus() != song.Playing)
		song.play();

	World::update(dt);
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
						std::unique_ptr<Enemy> enemy(new Enemy(sfx,textures,this,player));
						enemy->setTexture(Textures::Enemy);
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
					bool bIsMenuPlayer = object["properties"].at(0)["value"] == "menuPlayer";
					if(object["properties"].at(0)["value"] == "player" || bIsMenuPlayer)
					{
						std::unique_ptr<Ninja> ninja(new Ninja(sfx, textures, this, &window));
						if(bIsMenuPlayer)
						{
							ninja->setCategory(Category::MenuPlayer & Category::Actor);
							ninja->setDir(1);
						}
						ninja->setTexture(Textures::Ninja);
						sf::Vector2u textureSize = ninja->getTextureSize();
						ninja->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
						ninja->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
						ninja->setPosition((float)object["x"] - textureSize.x/2.f,(float)object["y"] - textureSize.y);
						ninja->setIsDynamic(true);
						player = ninja.get();
						addNode(&ninja,Entity);
					}
				}
			}
		}
	}
}

Level::~Level()
{
	song.stop();
}



