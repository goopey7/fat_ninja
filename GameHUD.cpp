//Copyright Sam Collier 2022

#include "GameHUD.h"
#include <sstream>

GameHUD::GameHUD(FontHolder& fonts, sf::RenderWindow& window)
	: window(&window)
{
	playerHealth = new Text(window,fonts.get(Fonts::Pixel));
	playerHealth->anchorTo(Anchor::TopLeft);
	enemiesKilled = new Text(window,fonts.get(Fonts::Arial));
	enemiesKilled->anchorTo(Anchor::BottomRight);
}

GameHUD::~GameHUD()
{
	delete playerHealth;
	delete enemiesKilled;
}

void GameHUD::fixedUpdateCurrent(const float dt)
{
	playerHealth->updatePosFromAnchor();
	enemiesKilled->updatePosFromAnchor();

	std::ostringstream oss;
	oss << "Killed: " << numEnemiesKilled;
	enemiesKilled->setText(oss.str());
}

void GameHUD::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(*enemiesKilled,states);
	target.draw(*playerHealth,states);
}

void GameHUD::addKill()
{
	numEnemiesKilled++;
}

void GameHUD::updateHealth(float health)
{
	std::ostringstream oss;
	oss << "Health: " << health;
	playerHealth->setText(oss.str());
}

