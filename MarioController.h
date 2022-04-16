//Copyright Sam Collier 2022
#pragma once

#include "gf/PlayerController.h"
#include "Mario.h"

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
			Teleport,
			DebugToggle,
		};

	protected:

	private:
		sf::RenderWindow* window;
		
};

