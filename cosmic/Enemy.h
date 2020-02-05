#pragma once
#include "Entity.h"
#include "Bullet.h"

class Enemy :
	public Entity
{
public:
	Enemy(sf::Texture *texture, sf::Vector2u pos, int lvl, bool canShoot, int type);
	Enemy(sf::Texture *texture, bool canShoot, bool canHeal, int lvl, sf::Vector2f(size), int type);
	~Enemy();
	std::vector<Bullet> bullets;
	int shootDelay, shootDelay_;
	void setSpeed(float a);
	void setHorSpeed(float a);
	bool isDead;
	bool canMove;
	int type;
	float horisontalSpeed;
	void shoot(sf::String file);
private:
	sf::Texture *texture;
	sf::Texture bulletText;
};

class Asteroid :
	public Entity {
public:

	Asteroid(sf::Texture *texture, sf::Vector2u windowSize, int lvl);
	Asteroid(sf::Texture *texture, sf::Vector2u windowSize, int lvl, int n, float y);
private:
	sf::Texture *texture;
};

