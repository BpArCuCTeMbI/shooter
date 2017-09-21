#include "StaticRect.h"
#include <iostream>

unsigned int StaticRect::objCounter = 0;

StaticRect::StaticRect(Game &game, sf::Vector2f& size, sf::Color fillColor, sf::Vector2f& position, float32 friction, const float32 &SCALE, float32 angVel) {
	udata.staticRectPtr = this;
	texture = nullptr;
	
	/*graphics init*/
	drwContainer.drwType = DrawableType::COLORED;
	drwContainer.rShape = new sf::RectangleShape();
	drwContainer.rShape->setSize(size);
	drwContainer.rShape->setFillColor(fillColor);
	/*shape origin is centered because of collision detection
	algorithm which uses center of mass as an origin*/
	drwContainer.rShape->setOrigin(size.x / 2, size.y / 2);

	/*physics init*/
	b2BodyDef bDef;
	bDef.position.Set(position.x / SCALE, position.y / SCALE);

	if (angVel == 0) {
		bDef.type = b2_staticBody;
		udata.type = STATIC_RECT;
	}
	else {
		bDef.type = b2_kinematicBody;
		udata.type = KINEMATIC_RECT;
		bDef.angularVelocity = angVel / SCALE;
	}
	body = game.world->CreateBody(&bDef);
	body->SetUserData((void*)&udata);


	b2PolygonShape bShape;
	bShape.SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	b2FixtureDef bFDef;
	bFDef.shape = &bShape;
	bFDef.friction = friction;
	rectFixture = body->CreateFixture(&bFDef);

	world = game.world;
	objCounter++;
}

StaticRect::StaticRect(Game &game, sf::Vector2i& size, sf::Vector2f& position, float32 friction, const float32 &SCALE, float32 angVel, const std::string& texPath) {
	udata.staticRectPtr = this;
	//graphics init
	drwContainer.drwType = DrawableType::TEXTURED;
	texture = new sf::Texture();
	if (!texture->loadFromFile(texPath)) {
		std::cerr << "failed to load rect texture" << std::endl;
	}
	
	texture->setRepeated(true);
	drwContainer.spr = new sf::Sprite(*texture, sf::IntRect(0, 0, size.x, size.y));
	drwContainer.spr->setOrigin(drwContainer.spr->getGlobalBounds().width / 2, drwContainer.spr->getGlobalBounds().height / 2);
	drwContainer.spr->setPosition(position);

	//physics init
	b2BodyDef bDef;
	bDef.position.Set(position.x / SCALE, position.y / SCALE);
	
	if (angVel == 0) {
		bDef.type = b2_staticBody;
		udata.type = STATIC_RECT;
	}
	else {
		bDef.type = b2_kinematicBody;
		udata.type = KINEMATIC_RECT;
		bDef.angularVelocity = angVel / SCALE;
	}
	body = game.world->CreateBody(&bDef);
	body->SetUserData((void*)&udata);

	b2PolygonShape bShape;
	bShape.SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	b2FixtureDef bFDef;
	bFDef.shape = &bShape;
	bFDef.friction = friction;
	rectFixture = body->CreateFixture(&bFDef);

	world = game.world;
	objCounter++;
}

StaticRect::~StaticRect() {

	world->DestroyBody(body);
	delete drwContainer.rShape;
	delete texture;
	delete drwContainer.spr;
	objCounter--;
	std::cout << "staticrect destructor finished" << std::endl;
}

b2Vec2 StaticRect::getPosition() {
	return body->GetPosition();
}

float32 StaticRect::getAngle() {
	return body->GetAngle();
}

void StaticRect::setPhysPosition(float32 x, float32 y) {
	body->SetTransform(b2Vec2(x, y), body->GetAngle());
}

void StaticRect::setPosition(float32 x, float32 y) {
	if (drwContainer.drwType == DrawableType::TEXTURED) {
		drwContainer.spr->setPosition(x, y);
	}
	else {
		drwContainer.rShape->setPosition(x, y);
	}
}

void StaticRect::setRotation(float32 angle) {
	if (drwContainer.drwType == DrawableType::TEXTURED) {
		drwContainer.spr->setRotation(angle);
	}
	else {
		drwContainer.rShape->setRotation(angle);
	}
}

void StaticRect::setOrigin(float32 x, float32 y) {
	if (drwContainer.drwType == DrawableType::TEXTURED) {
		drwContainer.spr->setOrigin(x, y);
	}
	else {
		drwContainer.rShape->setOrigin(x, y);
	}
}

void StaticRect::setDrawableState(float32 x, float32 y, float32 angle) {
	setPosition(x, y);
	setRotation(angle);
}


DrawableContainer& StaticRect::getDrawableContainer() {
		return drwContainer;
}
