//Copyright Sam Collier 2022
#pragma once

#include "gf/PlayerController.h"
#include "Ninja.h"
#include "gf/World.h"
#include "Shuriken.h"

class NinjaController : public PlayerController
{
	public:
		NinjaController(sf::RenderWindow* window);
		~NinjaController();

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

