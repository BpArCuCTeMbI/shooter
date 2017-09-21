#ifndef STATICRECT_H
#define STATICRECT_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "UData.h"
#include "DrawableContainer.h"

class StaticRect {
protected:
	sf::Texture* texture;

	DrawableContainer drwContainer;

	b2Body *body;
	b2Fixture *rectFixture;
	b2World *world;
	
	static unsigned int objCounter;
	
	uData udata;

public:
	StaticRect(Game &game, sf::Vector2f& size, sf::Color fillColor, sf::Vector2f& position, float32 friction, const float32 &SCALE, float32 angVel);
	/*in case of textured rectangle, size parameter depends on texture size and should be chosen correctly by user*/
	StaticRect(Game& game, sf::Vector2i& size, sf::Vector2f& position, float32 friction, const float32& SCALE, float32 angVel, const std::string& texPath);

	~StaticRect();

	b2Vec2 getPosition();
	float32 getAngle();
	void setPosition(float32 x, float32 y);
	void setPhysPosition(float32 x, float32 y);
	void setRotation(float32 angle);
	void setOrigin(float32 x, float32 y);
	void setDrawableState(float32 x, float32 y, float32 angle);

	DrawableContainer& StaticRect::getDrawableContainer();
};

#endif