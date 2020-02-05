#include "Background.h"



Background::Background(sf::Vector2f(size), sf::Color color)
{
	//this->backg.setFillColor(color);
	//this->backg.setSize(size);
}

Background::Background(sf::Vector2f(size), sf::Texture *texture) {
	this->backg.setTexture(*texture);
}
void Background::drawTo(sf::RenderWindow *window) {
	window->draw(this->backg);
}
Background::~Background()
{
}
