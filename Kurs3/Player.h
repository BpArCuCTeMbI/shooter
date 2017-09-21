#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <AnimatedSprite.hpp>
#include "AnimationContainer.h"
#include "Game.h"
#include "Bullet.h"
#include <iostream>
#include <string>
#include <list>
#include "UData.h"

class Player {

protected:
	const float32 SCALE;

	Game *game_;

	sf::Vector2f sfShapeSize;

	sf::Texture* texture;
	sf::Texture* bulTex;
	//sf::Texture* explosionTex;

	AnimatedSprite* spr;
	Animation* currentAnimation;
	
	b2Body* pBody;

	sf::Time cooldown;
	sf::Clock cdClock;
	sf::Time cdElapsedTime;

	sf::Clock frameClock;
	sf::Time frameTime;
	
	AnimationContainer* animation;

	b2World* world;

	uData udata;

	int health;
	bool shooting;
	bool coold;

public:
	std::list<Bullet*> bList;
	Player(const std::string& texPath, Game &game, b2Vec2 spawnPos, sf::Vector2f &size, float32 density, float32 friction, objectType objType, const std::string& bulTexPath);

	~Player();

	void updateFrameTime();
	void playAnimation();
	void updateAnimation();
	void decideAnimation();

	void setPosition(float32 x, float32 y);
	void setRotation(float32 angle);
	void setDrawableState(float32 x, float32 y, float32 angle);
	void setOrigin(float32 x, float32 y);

	b2Vec2 getLinearVelocity();
	float32 getAngularVelocity();

	AnimatedSprite* getDrawable();
	bool isOnGround();

	void applyLinearImpulseToCenter(b2Vec2 imp);
	void applyForceToCenter(b2Vec2 force);

	b2Vec2 getPosition();
	float32 getAngle();
	sf::Vector2f getShapeSize();

	void shoot();
	bool isShooting();
	void updateCoolDown();
	bool isAtCoolDown();

	void handleControls();
	void processBullets();

	void decreaseHealth();
	int getHealth();

	objectType getType();

	Player* getObjPtr();
};

#endif
