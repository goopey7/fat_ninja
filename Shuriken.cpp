//Copyright Sam Collier 2022

#include "Shuriken.h"
#include <cmath>

Shuriken::Shuriken(const TextureHolder& textures, World* world)
	: Actor(textures,world)
{
	//rotationSpeed = 500.f;

	collisionBox.left = 3.f;
	collisionBox.top = 3.f;

	collisionBox.width = sprite.getTextureRect().width * sprite.getScale().x - collisionBox.left;
	collisionBox.height = sprite.getTextureRect().height * sprite.getScale().y - collisionBox.top;

	collisionBox.width -= 5.f;
	collisionBox.height -= 0.f;
}

void Shuriken::setupTarget(sf::Vector2f target)
{
	dir = Vector::normalize(sf::Vector2f(target.x,target.y) - getWorldPosition());
	velocity = dir * speed;
}

void Shuriken::onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
	if(std::fabs(contactNormal.x) != 0.f)
		velocity.y = 0.f;
	else if(std::fabs(contactNormal.y) != 0.f)
		velocity.x = 0.f;
}

