#pragma once
#include "SFML/Graphics.hpp"


#include "tinyc2.h"



class collision
{
public:

	bool static isCollided(const sf::Sprite& object1, const sf::Sprite& object2);

};