//Copyright Sam Collier 2022
#include "Mario.h"
#include <cmath>

Mario::Mario(const TextureHolder& textures, World* world, sf::RenderWindow* window)
	: Actor(textures,world), window(window), view(window->getView())
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
}

void Mario::fixedUpdateCurrent(const float dt)
{
	Actor::fixedUpdateCurrent(dt);

	if(thrownShuriken != nullptr)
	{
		if(thrownShuriken->hasHitWall() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// TODO INSERT CODE FOR INITIAL CALCULATIONS
			state = Swinging;
		}
		else if(thrownShuriken->hasHitWall())
		{
			state = Normal;
			thrownShuriken = nullptr;
		}
	}

	switch(state)
	{
		case Normal:
			{
				velocity.x = dir.x * maxSpeed;
				velocity.y += gravity * dt;
			}
			break;

		case Swinging:
			{
				// TODO APPLY SWING PHYSICS
				velocity = {0.f,0.f};
			}
			break;
	}
	updateView();
}

unsigned int Mario::getCategory() const
{
	return Category::PlayerCharacter | Category::Actor;
}

void Mario::jump()
{
	if(bCanJump)
		velocity.y = -jumpSpeed;
	bCanJump = false;
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

void Mario::onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
	if(contactNormal.y == -1.f)
	{
		bCanJump = true;
	}
}

void Mario::setShuriken(Shuriken& shuriken)
{
	thrownShuriken = &shuriken;
}

