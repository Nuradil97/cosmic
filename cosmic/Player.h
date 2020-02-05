#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <vector>
#include "var.h"
#include "Enemy.h"

class Player :
	public Entity
{
public:

	//STL template container
	std::vector<Bullet> bullets;
	Player(sf::Texture *texture);
	void updateMoves();
	bool isDead;
	void resetHP();
	void resetBuffs();
	void setLvl(std::vector<Enemy> enemies, int score, int &d1_, int &d2_, int &spawnDelay_, int &astrDelay, int &mltpl, int& shootDelay);
	void heal(int HP);
	void healMax();
};

