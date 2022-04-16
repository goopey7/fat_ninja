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
		Mario,
		Size,
	};
}
namespace Fonts
{
	enum ID
	{
		// insert Font IDs here
	};
}
// insert more enums for additional types here

// Typedefs to make code more readable for commonly used Resources
typedef ResourceHolder<sf::Texture,unsigned int> TextureHolder;
typedef ResourceHolder<sf::Font,Fonts::ID> FontHolder;

