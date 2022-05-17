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

void Game::initLevelFiles()
{
	levelFiles.push_back("levels/mainMenu.tmj");
	levelFiles.push_back("levels/grappleTest.json");
	levelFiles.push_back("levels/wallJumpTest.tmj");
	levelFiles.push_back("levels/challenge.tmj");
}

Game::Game()
{ 
	initWindow();
	initLevelFiles();
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

	if((*world)->gameOver())
	{
		if(inGameOver)
		{
			if(world->get()->getID()+1 != levelFiles.size())
				world->get()->changeWorld(new Level(*window,world,levelFiles[levelDiedOn+1]));
			else
				world->get()->changeWorld(new MainMenu(*window,world,"levels/mainMenu.tmj"));
			inGameOver = false;
		}
		else
		{
			levelDiedOn = world->get()->getID();
			(*world)->changeWorld(new GameOver(*window,world,world->get()->getID(),levelFiles));
			inGameOver = true;
		}
	}

	// advance to the next level
	else if((*world)->complete())
	{
		if(inGameOver)
		{
			inGameOver = false;
			world->get()->changeWorld(new Level(*window,world,levelFiles[levelDiedOn]));
		}
		else
		{
			if(world->get()->getID()+1 != levelFiles.size())
				world->get()->changeWorld(new Level(*window,world,levelFiles[world->get()->getID()+1]));
			else world->get()->changeWorld(new MainMenu(*window,world,"levels/mainMenu.tmj"));
		}
	}
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
	const sf::Time TimeUntilMoreOpacityAdded = sf::seconds(splashScreenTime/2.f/255.f);
	sf::Clock timer;
	sf::Time prevTime = sf::Time::Zero;
	sf::Time timeBetweenTicks = sf::Time::Zero;

	bool bDoneGoingUp = false;

	sf::Texture splashTexture;
	splashTexture.loadFromFile("art/splashScreen.png");
	splashScreen.setTexture(splashTexture);
	float opacity = 0;
	while(!bSplashScreenDone)
	{
		splashScreen.setColor(sf::Color(255,255,255,opacity));
		sf::Time currentTime = timer.getElapsedTime();
		sf::Time dt = currentTime - prevTime;
		timeBetweenTicks += dt;
		prevTime = currentTime;

		splashScreen.setOrigin(splashTexture.getSize().x/2.f,splashTexture.getSize().y/2.f);
		splashScreen.setPosition(window->getSize().x/2.f,window->getSize().y/2.f);

		if(opacity<255 && timeBetweenTicks >= TimeUntilMoreOpacityAdded && !bDoneGoingUp)
		{
			opacity += 1;
			timeBetweenTicks -= TimeUntilMoreOpacityAdded;
		}
		else if(opacity == 255)
			bDoneGoingUp = true;

		if(timeBetweenTicks >= TimeUntilMoreOpacityAdded && bDoneGoingUp && opacity > 0)
		{
			opacity-=1;
			timeBetweenTicks -= TimeUntilMoreOpacityAdded;
		}
		else if(opacity == 0)
			bSplashScreenDone = true;

		// handle events
		sf::Event e;
		while(window->pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				window->close();
			else if(e.type == sf::Event::Resized)
				changeScale();
		}

		// render
		window->clear();
		window->draw(splashScreen);
		window->display();
	}
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

