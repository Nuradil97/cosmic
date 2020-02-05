#include "text.h"



text::text(Font *font, int charSize, Color color, float x, float y)
{
	this->lbl.setCharacterSize(charSize);
	this->lbl.setFillColor(color);
	this->lbl.setPosition(x, y);
	this->lbl.setFont(*font);
}

text::text(Font *font, int charSize, Color color, float x, float y, std::string txt) {
	this->lbl.setCharacterSize(charSize);
	this->lbl.setFillColor(color);
	this->lbl.setPosition(x, y);
	this->lbl.setFont(*font);
	this->lbl.setString(txt);
}

void text::setStr(std::string str) {
	this->lbl.setString(str);
}

void text::setPos(float x, float y) {
	this->lbl.setPosition(x, y);
}

FloatRect text::getBounds() {
	return this->lbl.getGlobalBounds();
}

void text::setSize(unsigned size) {
	this->lbl.setCharacterSize(size);
}
void text::drawTo(RenderWindow *window) {
	window->draw(this->lbl);
}