#pragma once
#include "Entity.h"
class Bullet :
	public Entity
{
public:
	Bullet(sf::Texture *texture, sf::Vector2f pos, float speed);
private:
	sf::Texture *texture;
};

