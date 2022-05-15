//Copyright Sam Collier 2022

#include "NinjaController.h"
#include <iostream>
#include <cmath>

enum Direction
{
	None = 0,
	Left = -1,
	Right = 1,
};

struct NinjaMover
{
	NinjaMover(Direction dir)
		: dir(dir)
	{
	}

	void operator() (Ninja& ninja, const float dt) const
	{
		ninja.setDir(dir);
	}

	Direction dir;
};

NinjaController::NinjaController(sf::RenderWindow* window)
	: window(window)
{
	keyBindings[sf::Keyboard::Space] = Jump;
	keyBindings[sf::Keyboard::A] = MoveLeft;
	keyBindings[sf::Keyboard::S] = Crouch;
	keyBindings[sf::Keyboard::D] = MoveRight;
	keyBindings[sf::Keyboard::P] = ShowPos;
	keyBindings[sf::Keyboard::V] = ShowVel;
	keyBindings[sf::Keyboard::Z] = ShowDir;
	keyBindings[sf::Keyboard::B] = DebugToggle;

	mouseBindings[sf::Mouse::Left] = Attack;

	// Pressed Actions
	pressedActions[Jump].action = derivedAction<Ninja>
		(
			[] (Ninja& ninja, const float dt)
			{
				ninja.jump();
			}
		);
	pressedActions[Crouch].action = derivedAction<Ninja>
		(
		 	[] (Ninja& ninja, const float dt)
			{
				ninja.crouch();
			}
		);
	pressedActions[MoveRight].action = derivedAction<Ninja>(NinjaMover(Direction::Right));
	pressedActions[MoveLeft].action = derivedAction<Ninja>(NinjaMover(Direction::Left));
	pressedActions[ShowPos].action = [] (Node& node, const float dt)
	{
		std::cout << node.getPosition().x << ',' << node.getPosition().y << '\n';
	};
	pressedActions[ShowVel].action = derivedAction<Ninja>(
			[] (Ninja& ninja, const float dt)
			{
				std::cout << ninja.getVelocity() << std::endl;
			}
			);

	pressedActions[ShowDir].action = derivedAction<Ninja>(
			[] (Ninja& ninja, const float dt)
			{
				std::cout << ninja.getDir() << std::endl;
			}
			);

	
    pressedActions[Attack].action = derivedAction<Ninja>(
		[window] (Ninja& ninja, const float dt)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			sf::Vector2f mWorldPos = window->mapPixelToCoords(mousePos);
			std::unique_ptr<Shuriken> shuriken(new Shuriken(ninja.getSfx(),ninja.getTextures(),ninja.getWorld()));
			shuriken->setTexture(Textures::Shuriken);
			sf::Vector2u textureSize = shuriken->getTextureSize();
			shuriken->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
			shuriken->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
			shuriken->setPosition(ninja.getWorldPosition());
			shuriken->setIsDynamic(true);
			shuriken->setupTarget(mWorldPos);
			shuriken->setOrigin(textureSize.x/2.f, textureSize.y/2.f);
			ninja.setShuriken(*shuriken.get());
			ninja.getWorld()->addNode(&shuriken,World::Tile);
		});

	pressedActions[DebugToggle].action = derivedAction<Actor>(
			[] (Actor& actor, const float dt)
			{
				actor.toggleDebugMode();
			}
			);

	// Released Actions
	std::function<void(Node&,const float dt)> ninjaStop = derivedAction<Ninja>
		(
		 [this] (Ninja& ninja, const float dt)
		 {
		 	if(ninja.getDir() == Direction::Right && !sf::Keyboard::isKeyPressed(getBindedKey(MoveRight)))
			{
				if(sf::Keyboard::isKeyPressed(getBindedKey(MoveLeft)))
					ninja.setDir(Direction::Left);
				else ninja.setDir(Direction::None);
			}
			else if(ninja.getDir() == Direction::Left && !sf::Keyboard::isKeyPressed(getBindedKey(MoveLeft)))
			{
				if(sf::Keyboard::isKeyPressed(getBindedKey(MoveRight)))
					ninja.setDir(Direction::Right);
				else ninja.setDir(Direction::None);
			}
		 }
		);
	releasedActions[MoveLeft].action = ninjaStop;
	releasedActions[MoveRight].action = ninjaStop;

	releasedActions[Crouch].action = derivedAction<Ninja>
		(
		 [] (Ninja& ninja, const float dt)
		 {
		 	ninja.stopCrouch();
		 }
		);

	// Init categroies
	for(auto &binding : heldActions)
	{
		binding.second.category = Category::PlayerCharacter;
	}
	for(auto &binding : pressedActions)
	{
		binding.second.category = Category::PlayerCharacter;
	}
	for(auto &binding : releasedActions)
	{
		binding.second.category = Category::PlayerCharacter;
	}
	pressedActions[DebugToggle].category = Category::Actor;
}

NinjaController::~NinjaController()
{
}

