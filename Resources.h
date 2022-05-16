//Copyright Sam Collier 2022
#pragma once

#include "gf/ResourceHolder.h"

namespace Textures
{
	enum ID
	{
		// insert texture IDs here
		Box,
		Bkg,
		Ninja,
		Shuriken,
		Enemy,
		Bullet,
		Size
	};
}
namespace Fonts
{
	enum ID
	{
		// insert Font IDs here
		Arial,
		Pixel,
		Size
	};
}
namespace Sfx
{
	enum ID
	{
		// insert Sound IDs here
		Grapple,
		Death,
		Size,
	};
}
// insert more enums for additional types here

// Typedefs to make code more readable for commonly used Resources
typedef ResourceHolder<sf::Texture,unsigned int> TextureHolder;
typedef ResourceHolder<sf::Font,unsigned int> FontHolder;
typedef ResourceHolder<sf::SoundBuffer,unsigned int> SoundHolder;
typedef ResourceHolder<sf::Sound,unsigned int> Player;

