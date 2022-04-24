//Copyright Sam Collier 2022
#pragma once

#include "gf/PlayerController.h"
#include "Mario.h"
#include "gf/World.h"
#include "Shuriken.h"

class MarioController : public PlayerController
{
	public:
		MarioController(sf::RenderWindow* window);
		~MarioController();

		enum Action
		{
			Jump,
			MoveLeft,
			Crouch,
			MoveRight,
			ShowPos,
			ShowVel,
			ShowDir,
			Attack,
			DebugToggle,
		};

	protected:

	private:
		sf::RenderWindow* window;
		
};

