#pragma once
#include <SFML\Graphics.hpp>

class Explosion
{
private:
	sf::Sprite sprite;

public:
	sf::Vector2f source;
	void drawTo(sf::RenderWindow *window);
	Explosion(sf::Texture *texture, sf::Vector2f(pos));
	~Explosion();

	unsigned stage;
	unsigned explosionTimer;
	unsigned explosionTimer_;
	void change();
	sf::Vector2f getSource();
	void explode();
	bool isOver();
};

