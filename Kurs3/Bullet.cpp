#include "Bullet.h"

Bullet::Bullet(sf::Texture* bulTex, Game *game, b2Vec2 spawnPos, sf::Vector2f &size, float32 density, float32 SCALE, Direction dir):SCALE_(SCALE), game_(game), colliding(false) {
	udata.dir = dir;
	udata.bulletPtr = this;
	udata.type = BULLET;

	sfShapeSize = size;
	texture = bulTex;

	animation = new AnimationContainer(*texture, udata.type);
	
	spr = new AnimatedSprite(sf::seconds(0.2f), true, false);
	spr->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));

	currentAnimation = &animation->bulletAnimationMoving;

	/*physics*/
	b2BodyDef bulDef;
	bulDef.position = b2Vec2(spawnPos.x / SCALE, spawnPos.y / SCALE);
	bulDef.type = b2_dynamicBody;
	bulDef.fixedRotation = true;
	bBody = game_->world->CreateBody(&bulDef);
	bBody->SetUserData((void*)&udata);

	b2PolygonShape bulShape;
	bulShape.SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	b2FixtureDef bulFDef;
	bulFDef.density = density;
	bulFDef.shape = &bulShape;
	bBody->CreateFixture(&bulFDef);
	world = game_->world;
}

Bullet::~Bullet() {
	world->DestroyBody(bBody);
	delete spr;
	delete animation;
	std::cout << "bullet destructor finished" << std::endl;
}

void Bullet::updateFrameTime() {
	frameTime = frameClock.restart();
}

void Bullet::playAnimation() {
	spr->play(*currentAnimation);
}

bool Bullet::isColliding() {
	return colliding;
}

void Bullet::decideAnimation() {
	sf::Vector2f scale = spr->getScale();
	if (udata.dir == left) {
		if (scale.x > 0) {
			spr->setScale(-scale.x, scale.y);
		}
		currentAnimation = &animation->bulletAnimationMoving;
	}
	else if (udata.dir == right) {
		if (scale.x < 0) {
			spr->setScale(-scale.x, scale.y);
		}
		currentAnimation = &animation->bulletAnimationMoving;
	}
	
	if (colliding) {
		currentAnimation = &animation->bulletAnimationHit;
	}
	
}

void Bullet::updateAnimation() {
	spr->update(frameTime);
}

b2Vec2 Bullet::getLinearVelocity() {
	return bBody->GetLinearVelocity();
}

float32 Bullet::getAngularVelocity() {
	return bBody->GetAngularVelocity();
}

AnimatedSprite* Bullet::getDrawable() {
	return spr;
}

void Bullet::applyLinearImpulseToCenter(b2Vec2 imp) {
	bBody->ApplyLinearImpulseToCenter(imp, true);
}

b2Vec2 Bullet::getPosition() {
	return bBody->GetPosition();
}

sf::Vector2f Bullet::getShapeSize() {
	return sfShapeSize;
}

void Bullet::setDrawableState(float32 x, float32 y) {
	spr->setPosition(x, y);
}

uData& Bullet::getUdata() {
	return udata;
}

b2Body* Bullet::getBody() {
	return bBody;
}

void Bullet::startContact() {
	colliding = true;
}