//Copyright Sam Collier 2022

#include "Box.h"
#include "gf/Vector.h"

Box::Box(const TextureHolder& textures, sf::RenderWindow* window)
	: Actor(textures), window(window)
{
}

void Box::updateCurrent(const float dt)
{
	Actor::updateCurrent(dt);

	if(bFollowMouse)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			sf::Vector2f dir = sf::Vector2f(mousePos) - getWorldPosition();
			dir = Vector::normalize(dir);
			velocity += dir * acceleration * dt;
		}
	}
	
	if(bFollowKbd)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			velocity.x += -acceleration*dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			velocity.x += acceleration*dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			velocity.y += -acceleration*dt;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			velocity.y += acceleration*dt;
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

void Box::followKbd()
{
	bFollowKbd = true;
}

void Box::stopKbd()
{
	bFollowKbd = false;
}

