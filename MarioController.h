//Copyright Sam Collier 2022
#pragma once

#include "gf/PlayerController.h"
#include "Mario.h"

class MarioController : public PlayerController
{
	public:
		MarioController();
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
		};

	protected:

	private:
		
};

