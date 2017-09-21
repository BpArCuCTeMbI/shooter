#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Game.h"
#include "AnimationContainer.h"
#include "UData.h"

class Bullet {
protected:
	const float32 SCALE_;
	Game* game_;

	uData udata;

	sf::Vector2f sfShapeSize;
	sf::Texture* texture;
	AnimatedSprite* spr;
	AnimationContainer* animation;
	Animation* currentAnimation;

	b2Body* bBody;

	sf::Clock frameClock;
	sf::Time frameTime;

	bool colliding;

	b2World* world;

public:
	Bullet(sf::Texture* bulTex, Game* game_, b2Vec2 spawnPos, sf::Vector2f &size, float32 density, float32 SCALE, Direction dir);
	~Bullet();

	void updateFrameTime();
	void playAnimation();
	void updateAnimation();
	void decideAnimation();
	void setDrawableState(float32 x, float32 y);

	bool isColliding();

	b2Vec2 getLinearVelocity();
	float32 getAngularVelocity();

	AnimatedSprite* getDrawable();
	void applyLinearImpulseToCenter(b2Vec2 imp);

	b2Vec2 getPosition();
	sf::Vector2f getShapeSize();

	uData& getUdata();

	b2Body* getBody();
	void startContact();
};

#endif