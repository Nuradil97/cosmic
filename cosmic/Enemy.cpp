#include "Enemy.h"



Enemy::Enemy(sf::Texture *texture, sf::Vector2u windowSize, int lvl, bool canShoot, int type)
{
	this->canMove = true;
	this->canShoot = false;
	this->lvl = lvl;
	this->type = type;
	this->speed = 4.f;
	this->HPStart = 1;
	this->HP = HPStart*lvl;
	this->canMove = true;
	this->horisontalSpeed = 3.f;
	this->shape.setTexture(*texture);
	this->shape.setScale(0.3f, 0.3f);
	this->shape.setPosition( rand() % windowSize.x - (int)(this->shape.getGlobalBounds().width), 0 - this->shape.getGlobalBounds().height);
}
Enemy::Enemy(sf::Texture *texture, bool canShoot, bool canHeal, int lvl, sf::Vector2f(size), int type) {
	this->shape.setTexture(*texture);
	this->setPos(rand() % WINDOW_SIZE_X - (int)(this->shape.getGlobalBounds().width), 0 - getSize().y);
	this->shape.setScale(size);
	this->lvl = lvl;
	this->type = type;
	this->HPStart = 1;
	this->canMove = true;
	this->horisontalSpeed = 1.f;
	this->HP = HPStart*lvl;
	this->canShoot = canShoot;
	this->canHeal = canHeal;
	this->isDead = true;
	this->canMove = true;
	this->shootDelay = 0;
	this->shootDelay_ = 50;
	this->speed = .2;
}

void Enemy::shoot(sf::String file) {
	File = file;
	bulletText.loadFromFile(File);
	if (this->canShoot) {
		if (shootDelay >= shootDelay_) {
			bullets.push_back(Bullet(&bulletText, this->getPos(),10));
			this->shootDelay = 0;
		}
		else shootDelay++;
	}
	else if (this->canDrop) {

	}

}

Asteroid::Asteroid(sf::Texture *texture, sf::Vector2u windowSize, int lvl) {
	this->lvl = lvl;
	this->speed = 3.f * lvl;
	this->HPStart = 1;
	this->HP = HPStart*lvl - 1;
	this->shape.setScale(1,1);
	this->shape.setTexture(*texture);
	this->shape.setTextureRect(sf::IntRect(rand() % 5 * 72, rand() % 4 * 72, 72, 72));
	this->shape.setPosition(rand() % windowSize.x - (int)(this->shape.getGlobalBounds().width), 0 - this->shape.getGlobalBounds().height);
}
Asteroid::Asteroid(sf::Texture *texture, sf::Vector2u windowSize, int lvl, int n, float y) {
	this->lvl = lvl;
	this->speed = 3.f * lvl;
	this->HPStart = 1;
	this->HP = HPStart*lvl - 1;
	this->shape.setScale(1, 1);
	this->shape.setTexture(*texture);
	this->shape.setTextureRect(sf::IntRect(rand() % 5 * 72, rand() % 4 * 72, 72, 72));
	this->shape.setPosition(0 + n*72, -72 + 72*y);
}

void Enemy::setSpeed(float a) {
	this->speed *= a;
}

void Enemy::setHorSpeed(float a) {
	this->horisontalSpeed *= a;
}

Enemy::~Enemy()
{
}

