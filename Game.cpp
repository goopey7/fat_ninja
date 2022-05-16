//Copyright Sam Collier 2022

#include "Game.h"

void Game::initWindow()
{
	std::ifstream ifs("config/window.cfg");
	sf::VideoMode windowSize(800,600);
	bool vSyncEnabled = false;
	if(ifs.is_open() && ifs.good())
	{
		std::getline(ifs,title);
		ifs >> windowSize.width >> windowSize.height;
		ifs >> vSyncEnabled;
	}
	else if(!ifs.good())
	{
		windowSize = sf::VideoMode(1920,1080);
		vSyncEnabled = false;
		std::filesystem::create_directory("config");
	}
	ifs.close();
	std::ofstream ofs("config/window.cfg",std::ofstream::out);
	ofs << title << '\n';
	ofs << std::to_string(windowSize.width) << " " << std::to_string(windowSize.height) << '\n';
	ofs << std::to_string(vSyncEnabled);
	ofs.close();
	window = new sf::RenderWindow(windowSize,title);
	window->setVerticalSyncEnabled(vSyncEnabled);
}

Game::Game()
{ 
	initWindow();
	world = new std::unique_ptr<World>(nullptr);
	world->reset(new MainMenu(*window,world,"levels/mainMenu.tmj"));
	worldPrev = world->get();
	std::cout << "GAME\n";
	std::cout << world << std::endl;
	pc = new NinjaController(window);
}

Game::~Game()
{
	delete pc;
	delete window;
	delete world;
}

void Game::changeScale()
{
	sf::FloatRect windowRect(0.f,0.f,window->getSize().x*world->get()->getViewScale(),window->getSize().y*world->get()->getViewScale());
	window->setView(sf::View(windowRect));
	worldPrev = world->get();
}

void Game::handleEvents()
{
	CommandQueue& commands = (*world)->getCommandQueue();
	sf::Event ev;
	if(world->get() != worldPrev)
		changeScale();
	while(window->pollEvent(ev))
	{
		pc->handleEvent(ev,commands);
		if(ev.type == sf::Event::Closed)
			window->close();

		// Scale view with window size
		else if(ev.type == sf::Event::Resized) 
		{
			changeScale();
		}

		else if(ev.type == sf::Event::KeyPressed)
		{
			if(ev.key.code == sf::Keyboard::Escape)
				bPause = !bPause;
		}
	}
	pc->handleHeldInput(commands);
}

void Game::update(const float dt)
{
	(*world)->update(dt);
}

void Game::fixedUpdate(const float dt)
{
	(*world)->fixedUpdate(dt);

	//TODO Game Over Screen!!
	if((*world)->gameOver())
		(*world)->changeWorld(new MainMenu(*window,world,"levels/mainMenu.tmj"));

	else if((*world)->complete())
		(*world)->changeWorld(new MainMenu(*window,world,"levels/mainMenu.tmj"));
}

void Game::render()
{
	window->clear();
	(*world)->draw();
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
		// Realtime Events
		handleEvents();

		// get the time
		sf::Time currentTime = timer.getElapsedTime();
		sf::Time dt = currentTime - prevTime;
		timeBetweenTicks += dt;
		prevTime = currentTime;

		if(!bPause)
		{
			update(dt.asSeconds());

		
		}

		// Fixed Time Events
		while(timeBetweenTicks >= TimePerFixedUpdate)
		{
			if(!bPause)
				fixedUpdate(TimePerFixedUpdate.asSeconds());
			// subtract a fixedUpdate worth of ticks
			timeBetweenTicks-=TimePerFixedUpdate;
		}

		// Rendering
		render();
	}
}

