//Copyright Sam Collier 2022

#include "MainMenuHUD.h"

MainMenuHUD::MainMenuHUD(FontHolder& fonts,sf::RenderWindow* window, std::unique_ptr<World>* currentWorld)
	: window(window), fonts(&fonts)
{
	std::cout << "HUD\n";
	std::cout << currentWorld << std::endl;
	this->currentWorld = currentWorld;
	playButton = new Button(*window,sf::Vector2f(300.f,300.f),sf::Vector2f(300.f,100.f),fonts.get(Fonts::Pixel),"Play Game");
}

MainMenuHUD::~MainMenuHUD()
{
	delete playButton;
}

void MainMenuHUD::updateCurrent(const float dt)
{
	sf::Vector2f centerPos = window->mapPixelToCoords(sf::Vector2i(0,0)) + Vector<unsigned int>::divide(window->getSize(),2);
	playButton->setPosition(centerPos);
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
		//currentWorld->get()->changeWorld(new Level(*window, currentWorld,"levels/wallJumpTest.tmj"));
	}
	else if(playButton->isHovered(sf::Color::Red))
	{}
	else
		playButton->setFillColor(sf::Color::Transparent);
}

void MainMenuHUD::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(*playButton,states);
}

