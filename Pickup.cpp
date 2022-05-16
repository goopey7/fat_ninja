//Copyright Sam Collier 2022

#include "Pickup.h"


// All Pickups are 8x8

Pickup::Pickup(Player& sounds, const TextureHolder& textures, World* currentWorld)
	: Actor(sounds,textures,currentWorld)
{
	setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
	setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
	bIsDynamic = true;
}

Pickup::~Pickup()
{
}

void Pickup::onPickup()
{
	die();
}

unsigned int Pickup::getCategory() const
{
	return Category::Actor | Category::Pickup;
}

void Pickup::onDynamicVsDynamicEnter(Actor* other)
{
	if(other->getCategory() & Category::PlayerCharacter)
	{
		onPickup();
	}
}
