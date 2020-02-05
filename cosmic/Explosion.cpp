#include "Explosion.h"

#include <iostream>

Explosion::Explosion(sf::Texture *texture, sf::Vector2f(pos))
{
	this->source = {0, 0};
	this->sprite.setTexture(*texture);
	this->sprite.setTextureRect(sf::IntRect(source.x * 400, source.y * 400, 400, 400));
	this->sprite.setPosition(pos);
	this->sprite.setScale(.4, .4);
	this->stage = 1;
	this->explosionTimer = 0;
	this->explosionTimer_ = 3;
}

void Explosion::change() {
	if (this->stage <= 9) { 
		if (this->explosionTimer < this->explosionTimer_) {
			this->explosionTimer++;
		}
		else if (this->explosionTimer = this->explosionTimer_) {
			
			this->sprite.setTextureRect(sf::IntRect(getSource().x * 400, getSource().y * 400, 400, 400));
			this->stage++;
			this->explosionTimer = 0;
		}
	}
}

sf::Vector2f Explosion::getSource() {
	switch (this->stage) {
	case 1:
		
		return { 0, 0 };
		break;
	case 2:
		
		return { 1 , 0 };
		break;
	case 3:
		return { 2 , 0 };
		break;
	case 4:
		return  { 0 , 1 };
		break;
	case 5:
		return { 1 , 1 };
		break;
	case 6:
		return { 1 , 2 };
		break;
	case 7:
		return { 2 , 0 };
		break;
	case 8:
		return { 2, 1 };
		break;
	case 9:
		return { 2 , 2 };
		break;
	default:
		stage = 10;
		break;
	}
	
}


Explosion::~Explosion()
{
}
bool Explosion::isOver() {
	if (this->stage >= 9)
	{
		
		return true;
	}
	else if (this->stage < 10) {
		return false;
	}
}
void Explosion::drawTo(sf::RenderWindow *window) {
	window->draw(this->sprite);
}

void Explosion::explode() {
	this->change();

}