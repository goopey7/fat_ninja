//Copyright Sam Collier 2022

#include "Shuriken.h"
#include <cmath>

Shuriken::Shuriken(const TextureHolder& textures, World* world)
	: Actor(textures,world)
{
	setCategory(Category::Shuriken | Category::Actor);
}

void Shuriken::setupTarget(sf::Vector2f target)
{
	dir = Vector<float>::normalize(sf::Vector2f(target.x,target.y) - getWorldPosition());
	velocity = dir * speed;
}

void Shuriken::onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
	// Stop sliding, but allow resolution to happen as normal
	if(std::fabs(contactNormal.x) != 0.f)
		velocity.y = 0.f;
	else if(std::fabs(contactNormal.y) != 0.f)
		velocity.x = 0.f;

	bHitWall = true;
}

bool Shuriken::hasHitWall() const
{
	return bHitWall;
}

void Shuriken::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	Actor::drawCurrent(target,states);
}

Shuriken::~Shuriken()
{
}

void Shuriken::stopMoving()
{
	velocity = sf::Vector2f(0.f,0.f);
	bHitWall = true;
}

void Shuriken::onDynamicVsDynamicEnter(Actor* other)
{
	if(other->getCategory() & Category::Enemy)
	{
		// apply damage to self
		other->applyDamage(getDamage());
		std::cout << "Hit Enemy!";
		other->die();
		die();
	}
}

