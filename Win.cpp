//Copyright Sam Collier 2022

#include "Win.h"
#include <iostream>

Win::Win(Player& sounds, const TextureHolder& textures, World* currentWorld)
	: Pickup(sounds,textures,currentWorld)
{
}

Win::~Win()
{
}

unsigned int Win::getCategory() const
{
	return Category::Actor | Category::Pickup | Category::WinPickup;
}

