//Copyright Sam Collier 2022
#pragma once

#include "gf/Node.h"
#include "Level.h"
#include "gf/Button.h"

class MainMenuHUD : public Node
{
	public:
		MainMenuHUD(sf::RenderWindow* window, std::unique_ptr<World>* currentWorld);
		~MainMenuHUD();
		virtual void updateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	protected:

	private:
		std::unique_ptr<World>* currentWorld = nullptr;
		Button* playButton;
		sf::RenderWindow* window;
		sf::Font font;
};

