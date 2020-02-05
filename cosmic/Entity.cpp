#include "Entity.h"

sf::Sprite Entity::getShape() {
	return shape;
}

int Entity::getHP() {
	return HP;
}
int Entity::getHPmax() {
	return HPStart*this->getLvl();
}
//void Entity::drawTo(sf::RenderWindow *window){
//	window->draw(this->shape);
//}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape);
}
sf::FloatRect Entity::getBounds() {
	return this->shape.getGlobalBounds();
}
int Entity::getLvl() {
	return this->lvl;
}
void Entity::setPos(float x, float y) {
	this->shape.setPosition(x,y);
}
void Entity::move(float x, float y) {
	if(this->canMove)
	this->shape.move(x, y);
}
void Entity::setLvl_(int n) {
	this->lvl = n;
}
sf::Vector2f Entity::getPos() {
	return this->shape.getPosition();
}

float Entity::getSpeed() {
	return speed;
}
void Entity::takeDamage(int lvl) {
	if (lvl <= 3) {
		HP = HP - 1;
	}
	if (lvl == 4) {
		HP = HP - 1;
	}
	if (lvl > 4) {
		HP = HP - 2;
	}
}

sf::Vector2f Entity::getSize()
{
	return shape.getScale();
}

void Entity::setHP(int n) {
	this->HP = n;
}