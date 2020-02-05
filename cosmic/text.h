#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class text
{
public:
	text(Font *font, int charSize, Color color, float x, float y);
	text(Font *font, int charSize, Color color, float x, float y, std::string txt);
	void setStr(std::string str);
	FloatRect getBounds();
	void setPos(float x, float y);
	void setSize(unsigned size);
	void drawTo(RenderWindow *window);

protected:
	Text lbl;
};

