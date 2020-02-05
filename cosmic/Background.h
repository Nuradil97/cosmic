#pragma once
#include <SFML\Graphics.hpp>

class Background
{
private:
	sf::Sprite backg;
public:
	Background(sf::Vector2f(size),sf::Color color);
	Background(sf::Vector2f(size), sf::Texture *texture);
	void drawTo(sf::RenderWindow *window);
	~Background();
};

