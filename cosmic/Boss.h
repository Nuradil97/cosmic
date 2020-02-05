#pragma once
#include "Entity.h"
#include "Bullet.h"

class Boss :
	public Entity
{
public:
	std::vector<Bullet> bullets;
	Boss(sf::String file, bool canShoot, bool canHeal,bool drops, int lvl, sf::Vector2f(size));
	sf::Texture bulletText;
	bool isDead;
	void shoot(sf::String file);
	int shootDelay, shootDelay_;
	Boss();
	~Boss();
};

