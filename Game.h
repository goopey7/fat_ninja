//Copyright Sam Collier 2022
#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include "MainMenu.h"
#include "EmptyLevel.h"
#include "Level.h"
#include "NinjaController.h"
#include "GameOver.h"

// Game/App wrapper
class Game
{
	public:
		Game();
		~Game();
		void initWindow();
		void initLevelFiles();

		void handleEvents();
		void update(const float dt);
		void fixedUpdate(const float dt);
		void render();
		void run();

	private:
		std::string title = "goopFramework Game";
		sf::RenderWindow* window;

		// For FixedUpdate
		const int TicksPerSec = 60;

		std::unique_ptr<World>* world;
		NinjaController* pc;

		bool bPause = false;

		float currentScale = 1.f;

		World* worldPrev;

		void changeScale();

		// map level IDs to level file paths
		std::vector<const char*> levelFiles;

		bool inGameOver = false;

		int levelDiedOn = -1;

		sf::Sprite splashScreen;
		bool bSplashScreenDone = false;
		int splashScreenTime = 3; // seconds
};

