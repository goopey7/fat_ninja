//Copyright Sam Collier 2022
#pragma once

#include "gf/Node.h"
#include "Level.h"
#include "gf/Button.h"
#include "gf/Text.h"

class MainMenuHUD : public Node
{
	public:
		MainMenuHUD(FontHolder& fonts,sf::RenderWindow* window, std::unique_ptr<World>* currentWorld);
		~MainMenuHUD();
		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpdateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	protected:

	private:
		std::unique_ptr<World>* currentWorld = nullptr;
		Button* playButton;
		Button* controls;
		Text* howToPlay;
		sf::RenderWindow* window;
		FontHolder* fonts;
		bool howToPlaySelected = false;
		bool playButtonClicked = false;
};

