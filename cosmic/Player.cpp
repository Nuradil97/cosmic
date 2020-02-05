#include "Player.h"
#include <cmath>
using namespace sf;
Player::Player(sf::Texture *texture)
{
	this->lvl = 1;
	this->HPStart = 10;
	this->isDead = false;
	this->HP = HPStart;
	this->canMove = true;
	//this->texture = texture;
	this->shape.setTexture(*texture);
	this->shape.setScale(.4f, .4f);
	this->setPos(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y - this->shape.getScale().y);
}

void Player::updateMoves() {
	if (Keyboard::isKeyPressed(Keyboard::Up))
		this->move(UP);
	if (Keyboard::isKeyPressed(Keyboard::Left))
		this->move(LEFT);
	if (Keyboard::isKeyPressed(Keyboard::Down))
		this->move(DOWn);
	if (Keyboard::isKeyPressed(Keyboard::Right))
		this->move(RIGHT);
}
void Player::healMax() {
	this->HP = 10 * lvl;
}
void Player::resetHP() {
	this->setHP(this->HPStart);
}
void Player::heal(int hp) {
	this->HP + hp;
}
void Player::resetBuffs() {
	this->lvl = 1;
}

void Player::setLvl(std::vector<Enemy> enemies, int score, int &d1_, int &d2_, int &spawnDelay_, int &astrDelay, int &mltpl,int &shootDelay) {
	if (score >= pow(10, lvl)) {
		lvl++;
		healMax();
		if (lvl <= 2) {
			d1_ -= 200;
			d2_ -= 10000;
			spawnDelay_ -= 10;
			astrDelay -= 5 * lvl;
			mltpl++;
			shootDelay--;
		}
		if (lvl > 2) {
			mltpl += 2;
			if(astrDelay>15)
				astrDelay -= 10;
			if (spawnDelay_ > 20)
				spawnDelay_ -= 20;
			if (d1_ > 400)
				d1_ -= 400;
			//if (shootDelay >= 15)
			//	shootDelay -= 3;
		}
		for (size_t i = 0; i < enemies.size(); i++) {
			enemies[i].setSpeed(lvl);
			enemies[i].setHorSpeed(lvl);
			if (enemies[i].canShoot) {
				enemies[i].shootDelay_ -= 5;
			}
		}
	}
}