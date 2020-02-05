#include "Bullet.h"



Bullet::Bullet(sf::Texture *texture, sf::Vector2f pos, float speed)
{	
	this->speed = 15.f;
	this->shape.setTexture(*texture);
	this->shape.setScale(1,1);
	this->shape.setPosition(pos);
}


