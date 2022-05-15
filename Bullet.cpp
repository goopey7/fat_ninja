//Copyright Sam Collier 2022

#include "Bullet.h"
#include <cmath>

Bullet::Bullet(const TextureHolder& textures, World* world)
	: Actor(textures,world)
{
	setCategory(Category::Bullet | Category::Actor);
}

void Bullet::setupTarget(sf::Vector2f target)
{
	dir = Vector<float>::normalize(sf::Vector2f(target.x,target.y) - getWorldPosition());
	velocity = dir * speed;
}

void Bullet::onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
	die();
}

bool Bullet::hasHitWall() const
{
	return bHitWall;
}

void Bullet::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	Actor::drawCurrent(target,states);
}

Bullet::~Bullet()
{
}

void Bullet::stopMoving()
{
	velocity = sf::Vector2f(0.f,0.f);
	bHitWall = true;
}

void Bullet::onDynamicVsDynamicEnter(Actor* other)
{
}

void Bullet::fixedUpdateCurrent(const float dt)
{
	Actor::fixedUpdateCurrent(dt);
	timeAlive+=dt;
	if(timeAlive>=lifeTime && !bIsBeingUsed)
	{
		die();
	}
}

void Bullet::setIsBeingUsed(bool isUsing)
{
	bIsBeingUsed = isUsing;
}

