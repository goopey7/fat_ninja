//Copyright Sam Collier 2022

#include "GameOverHUD.h"

GameOverHUD::GameOverHUD(FontHolder& fonts, sf::RenderWindow& window, bool& bComplete, bool& bGameOver)
	: window(&window),fonts(&fonts),bComplete(&bComplete),bGameOver(&bGameOver)
{
	restartButton = new Button(window,sf::Vector2f(0.f,0.f),sf::Vector2f(300.f,100.f),fonts.get(Fonts::Pixel),
			"Restart Level");
	nextLevelButton = new Button(window,sf::Vector2f(0.f,0.f),sf::Vector2f(300.f,100.f),fonts.get(Fonts::Pixel),"Next Level");
	gameOverMessage = new Text(window,fonts.get(Fonts::Pixel));
	gameOverMessage->setText("You Died!");
	gameOverMessage->setFontSize(30);
	gameOverMessage->anchorTo(Anchor::Center);
}

GameOverHUD::~GameOverHUD()
{
}

void GameOverHUD::updateCurrent(const float dt)
{
	if(restartButton->isClicked(sf::Color::Cyan))
	{
	}
	else if(restartButton->isHeld(sf::Color::Green))
	{
	}
	else if(restartButton->isReleased(sf::Color::Magenta))
	{
		*bComplete = true;
	}
	else if(restartButton->isHovered(sf::Color::Red))
	{}
	else
		restartButton->setFillColor(sf::Color::Transparent);

	if(nextLevelButton->isClicked(sf::Color::Cyan))
	{
	}
	else if(nextLevelButton->isHeld(sf::Color::Green))
	{
	}
	else if(nextLevelButton->isReleased(sf::Color::Magenta))
	{
		*bGameOver = true;
	}
	else if(nextLevelButton->isHovered(sf::Color::Red))
	{}
	else
		nextLevelButton->setFillColor(sf::Color::Transparent);
}

void GameOverHUD::fixedUpdateCurrent(const float dt)
{
	sf::Vector2f centerPos = window->mapPixelToCoords(sf::Vector2i(0,0)) + Vector<unsigned int>::divide(window->getSize(),2);
	centerPos.y += 120.f;
	restartButton->setPosition(centerPos);
	nextLevelButton->setPosition(centerPos + sf::Vector2f(0.f,120.f));
	gameOverMessage->updatePosFromAnchor();
}

void GameOverHUD::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(*restartButton,states);
	target.draw(*nextLevelButton,states);
	target.draw(*gameOverMessage,states);
}

