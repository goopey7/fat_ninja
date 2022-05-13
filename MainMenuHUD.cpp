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
	if(playButton->isClicked(sf::Color::Cyan))
	{
	}
	else if(playButton->isHeld(sf::Color::Green))
	{}
	else if(playButton->isReleased(sf::Color::Magenta))
	{
		std::cout << currentWorld << std::endl;
		currentWorld->reset(new Level(*window, currentWorld,"levels/grappleTest.json"));
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

