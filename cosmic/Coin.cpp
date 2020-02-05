#include "Coin.h"



Coin::Coin(sf::Texture *text, sf::Vector2f(pos))
{
	this->source = { 0,0 };

	
	this->sprite.setTexture(*text);
	this->sprite.setPosition(pos.x + 20, pos.y - 80);
	this->sprite.setScale(0.5,0.5);
	this->sprite.setTextureRect(sf::IntRect(stage-1 * 116.666, 0, 116.666, 200));
	this->stage = 1;
	this->timer = 0;
	this->timer_ = 5;
	this->movespeed = 8;
}

void Coin::change() {
	if (this->stage <= 6) {
		if (timer < timer_) {
			timer++;
			std::cout << stage << std::endl;
		}
		else if (timer >= timer_) {
			this->sprite.setTextureRect(sf::IntRect(getSource().x * 116.666, getSource().y * 200, 116.666, 200));
			this->stage++;
			this->timer = 0;
			std::cout << stage << std::endl;
		}
	}
	else if (stage >= 6) stage = 1;
	
}

sf::Vector2f Coin::getSource() {
	switch (stage)
	{
	case 1:
		return { 0, 0 };
	case 2:
		return { 1, 0 };
	case 3:
		return { 2, 0 };
	case 4:
		return { 3, 0 };
	case 5:
		return { 4, 0 };
	case 6:
		return { 5, 0 };
	default:
		stage = 7;
		break;
	}
}

void Coin::move() {
	this->sprite.move(0, movespeed);
}
void Coin::drawTo(sf::RenderWindow* window) {
	window->draw(this->sprite);
}