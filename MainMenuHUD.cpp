//Copyright Sam Collier 2022

#include "MainMenuHUD.h"

MainMenuHUD::MainMenuHUD(FontHolder& fonts,sf::RenderWindow* window, std::unique_ptr<World>* currentWorld)
	: window(window), fonts(&fonts)
{
	std::cout << "HUD\n";
	std::cout << currentWorld << std::endl;
	this->currentWorld = currentWorld;
	playButton = new Button(*window,sf::Vector2f(300.f,300.f),sf::Vector2f(300.f,100.f),fonts.get(Fonts::Pixel),"Play Game");
	controls = new Button(*window,sf::Vector2f(300.f,300.f),sf::Vector2f(300.f,100.f),fonts.get(Fonts::Pixel), "How to play");
	howToPlay = new Text(*window,fonts.get(Fonts::Arial));
	std::ostringstream oss;
	oss << "Movement : WASD\nJump : SPACE\nAttack : LMB\nGrapple : LMB (Held)\nDebug Toggle : B\nPause : ESC\n\n";
	oss << "Find the W pickup!";
	howToPlay->setText(oss.str());
	howToPlay->anchorTo(Anchor::Center);
	howToPlay->setFontSize(60);
}

MainMenuHUD::~MainMenuHUD()
{
	/*
	delete playButton;
	delete controls;
	delete howToPlay;
	*/
}

void MainMenuHUD::updateCurrent(const float dt)
{
	if(!playButtonClicked)
	{
		if(playButton->isClicked(sf::Color::Cyan))
		{
		}
		else if(playButton->isHeld(sf::Color::Green))
		{
		}
		else if(playButton->isReleased(sf::Color::Magenta))
		{
			std::cout << currentWorld << std::endl;
			currentWorld->get()->changeWorld(new Level(*window, currentWorld,"levels/grappleTest.json"));
			playButtonClicked = true;
		}
		else if(playButton->isHovered(sf::Color::Red))
		{}
		else
			playButton->setFillColor(sf::Color::Transparent);

		if(controls->isClicked(sf::Color::Cyan))
		{
		}
		else if(controls->isHeld(sf::Color::Green))
		{
		}
		else if(controls->isReleased(sf::Color::Magenta))
		{
			howToPlaySelected = !howToPlaySelected;
		}
		else if(controls->isHovered(sf::Color::Red))
		{}
		else
			controls->setFillColor(sf::Color::Transparent);
	}
}

void MainMenuHUD::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	if(!howToPlaySelected)
	{
		target.draw(*playButton,states);
	}
	else
		target.draw(*howToPlay,states);
	target.draw(*controls,states);
}

void MainMenuHUD::fixedUpdateCurrent(const float dt)
{
	if(!howToPlaySelected)
	{
		sf::Vector2f centerPos = window->mapPixelToCoords(sf::Vector2i(0,0)) + Vector<unsigned int>::divide(window->getSize(),2);
		playButton->setPosition(centerPos);
		controls->setPosition(centerPos + sf::Vector2f(0.f,150.f));
		controls->setText("How to play");
	}
	else
	{
		sf::Vector2f bottomCenter = window->mapPixelToCoords(sf::Vector2i(0,0)) + Vector<unsigned int>::divide(window->getSize(),2);
		bottomCenter.y = window->mapPixelToCoords(sf::Vector2i(window->getSize())).y;
		controls->setPosition(bottomCenter + sf::Vector2f(0.f,-100.f));
		controls->setText("Go Back");
		howToPlay->updatePosFromAnchor();
	}
}

