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
	sprite.setScale({1.2f,1.2f});

	collisionBox.left = 3.f;
	collisionBox.top = 3.f;

	collisionBox.width = sprite.getTextureRect().width * sprite.getScale().x - collisionBox.left;
	collisionBox.height = sprite.getTextureRect().height * sprite.getScale().y - collisionBox.top;

	collisionBox.width -= 5.f;
	collisionBox.height -= 0.f;

	box.setSize(sf::Vector2f(collisionBox.width,collisionBox.height));
	box.setPosition(collisionBox.left,collisionBox.top);

	sf::View view = window->getView();
	view.setSize(240.f*1.5f, 135.f*1.5f);
	window->setView(view);

	updateView();
}

void Mario::handleAnimations(const float dt)
{	
	if(fabs(velocity.x) != 0.f)
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

	if(!bOnFloor)
	{
		// APPLY GRAVITY
		velocity.y += gravity*dt;
	}
	else velocity.y = 0.f;

	if(fabs(velocity.x) < maxSpeed)
	{
		velocity.x += dir.x * acceleration * dt;
	}
	else
	{
		velocity.x = dir.x * maxSpeed;
	}

	if (fabs(velocity.x) < fabs(acceleration) && dir.x == 0.f)
	{
		velocity.x = 0.f;
	}

	if(!(dir.x >= 0.f && bCanMoveRight || dir.x <=0.f && bCanMoveLeft))
	{
		velocity.x = 0.f;
	}
	move(velocity*dt);
	displacementFromLastFrame = velocity*dt;
	updateView();
}

unsigned int Mario::getCategory() const
{
	return Category::PlayerCharacter | Category::Actor;
}

void Mario::jump()
{
	bOnFloor = false;
	velocity.y = -jumpSpeed;
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

void Mario::onCollisionEnter(Actor* other, unsigned int sides, const sf::FloatRect& overlap)
{
	//std::cout << overlap.left << " , " << overlap.top << " , " << overlap.width << " , " << overlap.height << '\n';

	if(sides & gf::Side::Bottom && !bOnFloor)
	{
		bOnFloor = true;
	}
	if(sides & gf::Side::Top)
	{
		velocity.y = 0.f;
	}
	if(sides & gf::Side::Bottom && bOnFloor)
	{
		setPosition(getPosition().x, overlap.top - sprite.getGlobalBounds().height - getCollisionBox().height - (overlap.top - overlap.height));
	}
}

void Mario::whileColliding(Actor* other, unsigned int sides, const sf::FloatRect& overlap)
{
	if((bOnFloor && other->getCollisionBox().top + other->getPosition().y < getPosition().y + getCollisionBox().top + getCollisionBox().width)
			|| (!bOnFloor))
	{
		if(sides & gf::Side::Right)
		{
			bCanMoveRight=false;
		}
		if(sides & gf::Side::Left)
		{
			bCanMoveLeft=false;
		}
	}
}

void Mario::onCollisionExit(Actor* other, unsigned int sides, const sf::FloatRect& overlap)
{
	
	if(sides & gf::Side::Bottom)
	{
		bOnFloor = false;
	}
	if(sides & gf::Side::Right)
	{
		bCanMoveRight = true;
	}

	if(sides & gf::Side::Left)
	{
		bCanMoveLeft = true;
	}
}

