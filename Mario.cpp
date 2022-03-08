//Copyright Sam Collier 2022

#include "Mario.h"
#include <cmath>

Mario::Mario(const TextureHolder& textures)
	: Actor(textures)
{
	setPosition(50.f,50.f);

	for(int i=0; i<walkFrames; i++)
		walk.addFrame(sf::IntRect(i*walkWidth,0,walkWidth,walkHeight));
	walk.setFrameSpeed(walkSpeed);

	sprite.setTexture(textures.get(Textures::Mario));
	sprite.setTextureRect(walk.getCurrentFrame());
	sprite.setScale({10.f,10.f});
}

void Mario::handleAnimations(const float dt)
{	
	if(Vector::size(velocity) != 0.f)
	{
		walk.play();
		walk.animate(dt);
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
		
	move(velocity*dt);
}

unsigned int Mario::getCategory() const
{
	return Category::PlayerCharacter;
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

