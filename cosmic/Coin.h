#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Coin
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f(source);
	unsigned stage;
	unsigned timer;
	unsigned timer_;
	std::string FILE;
	
	float movespeed;
public:
	void change();
	sf::Vector2f getSource();
	Coin(sf::Texture *text, sf::Vector2f(pos));
	void move();
	void drawTo(sf::RenderWindow* window);
	float getY() {
		return this->sprite.getPosition().y;
	}
	sf::FloatRect getBounds() {
		return this->sprite.getGlobalBounds();
	}
};

