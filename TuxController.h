//Copyright Sam Collier 2022
#pragma once

#include "goopFramework/PlayerController.h"

class TuxController : public PlayerController
{
	public:
		TuxController();
		~TuxController();

		enum Action
		{
			MoveUp,
			MoveLeft,
			MoveDown,
			MoveRight,
			ShowPos
		};

	protected:

	private:
		
};

