#ifndef DRAWABLECONTAINER_H
#define DRAWABLECONTAINER_H
#include "SFML\Graphics.hpp"

enum DrawableType{TEXTURED, COLORED, EMPTY};

struct DrawableContainer {
	sf::Sprite* spr;
	sf::RectangleShape *rShape;
	DrawableType drwType;

	DrawableContainer();
};

#endif

