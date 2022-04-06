//Copyright Sam Collier 2022

#include "Game.h"

void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1920,1080),title);
	window->setVerticalSyncEnabled(true);
}

Game::Game()
{ 
	initWindow();
	world = new Level(*window);
}

Game::~Game()
{
	delete window;
	delete world;
}

void Game::handleEvents()
{
	CommandQueue& commands = world->getCommandQueue();
	sf::Event ev;
	while(window->pollEvent(ev))
	{
		if(ev.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update(const float dt)
{
	world->update(dt);
}

void Game::fixedUpdate(const float dt)
{
	world->fixedUpdate(dt);
}

void Game::render()
{
	window->clear();
	world->draw();
	window->display();
}

void Game::run()
{
	const sf::Time TimePerFixedUpdate = sf::seconds(1.f/TicksPerSec);
	sf::Clock timer;
	sf::Time prevTime = sf::Time::Zero;
	sf::Time timeBetweenTicks = sf::Time::Zero;
	
	// GAME LOOP
	while(window->isOpen())
	{
		// get the time
		sf::Time currentTime = timer.getElapsedTime();
		sf::Time dt = currentTime - prevTime;
		timeBetweenTicks += dt;
		prevTime = currentTime;

		// Realtime Events
		handleEvents();
		update(dt.asSeconds());

		// Fixed Time Events
		while(timeBetweenTicks >= TimePerFixedUpdate)
		{
			fixedUpdate(TimePerFixedUpdate.asSeconds());
			// subtract a fixedUpdate worth of ticks
			timeBetweenTicks-=TimePerFixedUpdate;
		}

		// Rendering
		render();
	}
}

