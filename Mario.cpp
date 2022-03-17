//Copyright Sam Collier 2022

#include "Mario.h"
#include <cmath>

Mario::Mario(const TextureHolder& textures, sf::RenderWindow* window)
	: Actor(textures), window(window), view(window->getView())
{
	for(int i=0; i<walkFrames; i++)
		walk.addFrame(sf::IntRect(i*walkWidth,0,walkWidth,walkHeight));
	walk.setFrameSpeed(walkSpeed);

	sprite.setTexture(textures.get(Textures::Mario));
	sprite.setTextureRect(walk.getCurrentFrame());
	sprite.setScale({10.f,10.f});

	collisionBox.left = 30.f;
	collisionBox.top = 30.f;

	collisionBox.width = sprite.getTextureRect().width * sprite.getScale().x - collisionBox.left;
	collisionBox.height = sprite.getTextureRect().height * sprite.getScale().y - collisionBox.top;

	collisionBox.width -= 40.f;
	collisionBox.height -= 20.f;

	box.setSize(sf::Vector2f(collisionBox.width,collisionBox.height));
	box.setPosition(collisionBox.left,collisionBox.top);
	updateView();
}

void Mario::handleAnimations(const float dt)
{	
	if(Vector::size(velocity) != 0.f)
	{
		walk.play();
		walk.animate(dt);
		updateView();
	}
	else
	{
		walk.pause();
		walk.setToInitialFrame();
	}
	if(velocity.x < 0.f)
		walk.setFlipped(true);
	else if(velocity.x > 0.f)
		walk.setFlipped(false);
	sprite.setTextureRect(walk.getCurrentFrame());
}

void Mario::updateCurrent(const float dt)
{
	handleAnimations(dt);
	if(fabs(velocity.x) < maxSpeed)
	{
		velocity += dir * acceleration * dt;
	}
	else
	{
		velocity = dir * maxSpeed;
	}

	if (fabs(velocity.x) < fabs(acceleration) && dir.x == 0.f)
	{
		velocity.x = 0.f;
	}

	if(dir.x >= 0.f || dir.x <=0.f)
		move(velocity*dt);
}

unsigned int Mario::getCategory() const
{
	return Category::PlayerCharacter | Category::Actor;
}

void Mario::jump()
{
}

void Mario::crouch()
{
}

void Mario::stopCrouch()
{
}

void Mario::setDir(int dir)
{
	this->dir.x = dir;
}

short Mario::getDir()
{
	return dir.x;
}

std::string Mario::getVelocity()
{
	return std::to_string(velocity.x) + " , " + std::to_string(velocity.y) + '\n';
}

void Mario::updateView()
{
	sf::View view = window->getView();
	view.setCenter(getWorldPosition());
	window->setView(view);
}

void Mario::onCollision(Actor* other, unsigned int sides)
{
	sf::Vector2f pos = getWorldPosition();
	sf::Vector2f otherPos = other->getWorldPosition();

	if(sides == gf::Side::Right)
	{
		setPosition(otherPos.x - getCollisionBox().width - getCollisionBox().left - 1.f, getWorldPosition().y);
	}
	else if (sides == gf::Side::Left)
	{
		setPosition(otherPos.x-getCollisionBox().left+other->getCollisionBox().width + 1.f, getWorldPosition().y);
	}
}

