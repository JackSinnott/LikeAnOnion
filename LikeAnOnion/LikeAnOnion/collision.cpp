#include "collision.h"

bool collision::isCollided(const sf::Sprite& object1, const sf::Sprite& object2) {
	
	c2AABB item1;
	item1.min = c2V(object1.getPosition().x - (object1.getGlobalBounds().width/2), object1.getPosition().y - (object1.getGlobalBounds().height / 2));
	item1.max = c2V(
		object1.getPosition().x + (object1.getGlobalBounds().width / 2),
		object1.getPosition().y + (object1.getGlobalBounds().height / 2));

	
	c2AABB item2;
	item2.min = c2V(object2.getPosition().x - (object2.getGlobalBounds().width / 2), object2.getPosition().y - (object2.getGlobalBounds().height / 2));
	item2.max = c2V(
		object2.getPosition().x + (object2.getGlobalBounds().width / 2),
		object2.getPosition().y + (object2.getGlobalBounds().height / 2));

	int result = 0;
	result = c2AABBtoAABB(item1, item2);
	bool collide = false;
	if (result != 0)
	{
		collide = true;
	}
	else 
	{
		collide = false;
	}
	return collide;
}
