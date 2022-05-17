//Copyright Sam Collier 2022
#pragma once

#include "gf/Text.h"
#include "gf/Button.h"
#include "Resources.h"

class GameOverHUD : public Node
{
	public:
		GameOverHUD(FontHolder& fonts, sf::RenderWindow& window, bool& bComplete);
		~GameOverHUD();
		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpdateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	private:
		Text* gameOverMessage = nullptr;
		Button* restartButton = nullptr;
		sf::RenderWindow* window = nullptr;
		FontHolder* fonts = nullptr;
		bool* bComplete = nullptr;
};

