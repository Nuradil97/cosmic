#include "Boss.h"

#include <iostream>

Boss::Boss()
{
}

Boss::Boss(sf::String file, bool canShoot, bool canHeal, bool drops, int lvl, sf::Vector2f(size)) {
	this->File = file;
	this->texture.loadFromFile(File);
	this->shape.setTexture(this->texture);
	this->setPos((WINDOW_SIZE_X / 2) - this->getSize().x, this->getSize().y);
	this->shape.setScale(size);
	this->setHP(100 * lvl);
	this->canShoot = canShoot;
	this->canHeal = canHeal;
	this->canDrop = drops;
	this->isDead = true;
	this->shootDelay = 0;
	this->shootDelay_ = 50;
	this->speed = 1.f;
}

void Boss::shoot(sf::String file) {
	File = file;
	bulletText.loadFromFile(File);
	if (this->canShoot) {
		if (shootDelay >= shootDelay_) {
			std::cout << "WORKS\n";
			bullets.push_back(Bullet(&bulletText, this->getPos(), 10.f));
			this->shootDelay = 0;
		}
		else shootDelay++;
	}
	else if (this->canDrop) {

	}

}

Boss::~Boss()
{
}
