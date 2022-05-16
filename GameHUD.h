//Copyright Sam Collier 2022
#pragma once

#include "gf/Node.h"
#include "gf/Text.h"
#include "Resources.h"

class GameHUD : public Node
{
	public:
		GameHUD(FontHolder& fonts, sf::RenderWindow& window);
		~GameHUD();
		virtual void fixedUpdateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
		void updateHealth(float health);
		void addKill();

	private:
		Text* playerHealth;
		Text* enemiesKilled;
		int numEnemiesKilled = 0;
		sf::RenderWindow* window;
};

