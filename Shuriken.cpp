//Copyright Sam Collier 2022

#include "Shuriken.h"
#include <cmath>

Shuriken::Shuriken(const TextureHolder& textures, World* world)
	: Actor(textures,world)
{
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

bool Shuriken::hasHitWall()
{
	return bHitWall;
}

void Shuriken::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite,states);
	if(bDebugMode)
		target.draw(box,states);
}

Shuriken::~Shuriken()
{
}

