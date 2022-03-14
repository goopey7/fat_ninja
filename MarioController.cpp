//Copyright Sam Collier 2022

#include "MarioController.h"
#include <iostream>
#include <cmath>

enum Direction
{
	None = 0,
	Left = -1,
	Right = 1,
};

struct MarioMover
{
	MarioMover(Direction dir)
		: dir(dir)
	{
	}

	void operator() (Mario& mario, const float dt) const
	{
		mario.setDir(dir);
	}

	Direction dir;
};

MarioController::MarioController(sf::RenderWindow* window)
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

	mouseBindings[sf::Mouse::Left] = Teleport;

	// Pressed Actions
	pressedActions[Jump].action = derivedAction<Mario>
		(
			[] (Mario& mario, const float dt)
			{
				mario.jump();
			}
		);
	pressedActions[Crouch].action = derivedAction<Mario>
		(
		 	[] (Mario& mario, const float dt)
			{
				mario.crouch();
			}
		);
	pressedActions[MoveRight].action = derivedAction<Mario>(MarioMover(Direction::Right));
	pressedActions[MoveLeft].action = derivedAction<Mario>(MarioMover(Direction::Left));
	pressedActions[ShowPos].action = [] (Node& node, const float dt)
	{
		std::cout << node.getPosition().x << ',' << node.getPosition().y << '\n';
	};
	pressedActions[ShowVel].action = derivedAction<Mario>(
			[] (Mario& mario, const float dt)
			{
				std::cout << mario.getVelocity() << std::endl;
			}
			);

	pressedActions[ShowDir].action = derivedAction<Mario>(
			[] (Mario& mario, const float dt)
			{
				std::cout << mario.getDir() << std::endl;
			}
			);

	pressedActions[Teleport].action = derivedAction<Mario>(
		[window] (Mario& mario, const float dt)
		{
			sf::Vector2f pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			mario.setPosition(pos);
			mario.updateView();
		});

	pressedActions[DebugToggle].action = derivedAction<Actor>(
			[] (Actor& actor, const float dt)
			{
				actor.toggleDebugMode();
			}
			);

	// Released Actions
	std::function<void(Node&,const float dt)> marioStop = derivedAction<Mario>
		(
		 [this] (Mario& mario, const float dt)
		 {
		 	if(mario.getDir() == Direction::Right && !sf::Keyboard::isKeyPressed(getBindedKey(MoveRight)))
			{
				if(sf::Keyboard::isKeyPressed(getBindedKey(MoveLeft)))
					mario.setDir(Direction::Left);
				else mario.setDir(Direction::None);
			}
			else if(mario.getDir() == Direction::Left && !sf::Keyboard::isKeyPressed(getBindedKey(MoveLeft)))
			{
				if(sf::Keyboard::isKeyPressed(getBindedKey(MoveRight)))
					mario.setDir(Direction::Right);
				else mario.setDir(Direction::None);
			}
		 }
		);
	releasedActions[MoveLeft].action = marioStop;
	releasedActions[MoveRight].action = marioStop;

	releasedActions[Crouch].action = derivedAction<Mario>
		(
		 [] (Mario& mario,const float dt)
		 {
		 	mario.stopCrouch();
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

MarioController::~MarioController()
{
}

