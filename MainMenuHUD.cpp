//Copyright Sam Collier 2022

#include "MainMenuHUD.h"

MainMenuHUD::MainMenuHUD(sf::RenderWindow* window, std::unique_ptr<World>* currentWorld)
	: window(window)
{
	std::cout << "HUD\n";
	std::cout << currentWorld << std::endl;
	this->currentWorld = currentWorld;
	playButton = new Button(*window,sf::Vector2f(20.f,20.f),sf::Vector2f(100.f,100.f),"Play Game");
}

MainMenuHUD::~MainMenuHUD()
{
	delete playButton;
}

void MainMenuHUD::updateCurrent(const float dt)
{
	if(playButton->isClicked())
	{
		std::cout << currentWorld << std::endl;
		currentWorld->reset(new Level(*window,"levels/grappleTest.json"));
	}
}

void MainMenuHUD::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(*playButton,states);
}

