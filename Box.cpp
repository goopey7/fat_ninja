//Copyright Sam Collier 2022

#include "Box.h"

Box::Box(const TextureHolder& textures, sf::RenderWindow* window)
	: Actor(textures), window(window)
{
}

void Box::updateCurrent(const float dt)
{
	if(bFollowMouse)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		setPosition(mousePos.x,mousePos.y);
	}
}

unsigned int Box::getCategory() const
{
	return Category::Actor;
}

void Box::onCollision()
{
	sprite.setColor(sf::Color::Red);
}


void Box::onCollisionExit()
{
	sprite.setColor(sf::Color::White);
}

void Box::followMouse()
{
	bFollowMouse = true;
}

