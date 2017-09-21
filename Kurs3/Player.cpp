#include "Player.h"


Player::Player(const std::string &texPath, Game &game, b2Vec2 spawnPos, sf::Vector2f &size, float32 density, float32 friction, objectType objType, const std::string& bulTexPath) : SCALE(6.0f), game_(&game) {
	shooting = false;
	coold = false;
	udata.type = objType;
	udata.playerPtr = this;
	sfShapeSize = sf::Vector2f(size.x, size.y);
	cooldown = sf::seconds(0.6f);
	cdElapsedTime = sf::Time::Zero;

	/*load textures*/
	bulTex = new sf::Texture();
	if (!bulTex->loadFromFile(bulTexPath)) {
		std::cerr << "failed to load bullet texture" << std::endl;
	}

	texture = new sf::Texture();
	if (!texture->loadFromFile(texPath)) {
		std::cerr << "failed to load player texture" << std::endl;
	}

	if (udata.type == PLAYER_1) {
		animation = new AnimationContainer(*texture, udata.type);
		udata.dir = left;
		currentAnimation = &animation->playerAnimationIdling;
		health = 10;

	}
	else if(udata.type == PLAYER_2) {
		animation = new AnimationContainer(*texture, udata.type);
		udata.dir = right;
		currentAnimation = &animation->player2AnimationIdling;
		health = 15;
	}

	/*init animation frames*/
	spr = new AnimatedSprite(sf::seconds(0.1f), true, false); //was 0.2f
	spr->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	
	
	/*init physics*/
	b2BodyDef pDef;
	pDef.position = b2Vec2(spawnPos.x / SCALE, spawnPos.y / SCALE);
	pDef.type = b2_dynamicBody;
	pDef.fixedRotation = true;

	pBody = game.world->CreateBody(&pDef);
	pBody->SetUserData((void*)&udata);

	b2PolygonShape pShape;
	pShape.SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	b2FixtureDef pFDef;
	pFDef.density = density;
	pFDef.friction = friction;
	pFDef.shape = &pShape;
	pBody->CreateFixture(&pFDef);

	world = game.world;
}

Player::~Player() {
	world->DestroyBody(pBody);
	delete spr;
	delete texture;
	delete bulTex;
	delete animation;
	std::cout << "player destructor finished" << std::endl;
}

void Player::updateFrameTime() {
	frameTime = frameClock.restart();
}

void Player::playAnimation() {
	spr->play(*currentAnimation);
}

void Player::decideAnimation() {

	b2Vec2 vel = getLinearVelocity();
	sf::Vector2f scale;
	bool onGround = isOnGround();

	if (udata.type == PLAYER_1) {

		if (shooting) {
			currentAnimation = &animation->playerAnimationShooting;
			//shooting = false;
		}
		else if (vel.x > 0.1 && onGround) {
			scale = spr->getScale();
			if (scale.x < 0) {
				spr->setScale(-scale.x, scale.y);
			}
			currentAnimation = &animation->playerAnimationMoving;
			udata.dir = right;
		}
		else if (vel.x < -0.1 && onGround) {
			scale = spr->getScale();
			if (scale.x > 0) {
				spr->setScale(-scale.x, scale.y);
			}
			currentAnimation = &animation->playerAnimationMoving;
			udata.dir = left;
		}

		else if ((vel.y < -0.1 || !onGround) || (vel.y > 0.1 || !onGround)) {
			scale = spr->getScale();
			if (vel.x > 0.1) {
				if (scale.x < 0) {
					spr->setScale(-scale.x, scale.y);
					udata.dir = right;
				}
			}
			else if (vel.x < -0.1) {
				if (scale.x > 0) {
					spr->setScale(-scale.x, scale.y);
					udata.dir = left;
				}
			}
			currentAnimation = &animation->playerAnimationJumping;
		}
		/*other animation decisions*/
		else {
			currentAnimation = &animation->playerAnimationIdling;
		}
	}
	else if (udata.type == PLAYER_2) {
		if (shooting) {
			currentAnimation = &animation->player2AnimationShooting;
			//shooting = false;
		}
		else if (vel.x > 0.1 && onGround) {
			scale = spr->getScale();
			if (scale.x < 0) {
				spr->setScale(-scale.x, scale.y);
			}
			currentAnimation = &animation->player2AnimationMoving;
			udata.dir = right;
		}
		else if (vel.x < -0.1 && onGround) {
			scale = spr->getScale();
			if (scale.x > 0) {
				spr->setScale(-scale.x, scale.y);
			}
			currentAnimation = &animation->player2AnimationMoving;
			udata.dir = left;
		}

		else if ((vel.y < -0.1 || !onGround) || (vel.y > 0.1 || !onGround)) {
			scale = spr->getScale();
			if (vel.x > 0.1) {
				if (scale.x < 0) {
					spr->setScale(-scale.x, scale.y);
					udata.dir = right;
				}
			}
			else if (vel.x < -0.1) {
				if (scale.x > 0) {
					spr->setScale(-scale.x, scale.y);
					udata.dir = left;
				}
			}
			currentAnimation = &animation->player2AnimationJumping;
		}
		/*other animation decisions*/
		else {
			currentAnimation = &animation->player2AnimationIdling;
		}
	}
}

void Player::updateAnimation() {
	spr->update(frameTime);
}

void Player::setOrigin(float32 x, float32 y) {
	spr->setOrigin(x, y);
}

void Player::setPosition(float32 x, float32 y) {
	spr->setPosition(x, y);
}

void Player::setRotation(float32 angle) {
	spr->setRotation(angle);
}

void Player::setDrawableState(float32 x, float32 y, float32 angle) {
	setPosition(x, y);
	setRotation(angle);
}

AnimatedSprite* Player::getDrawable() {
	return spr;
}

bool Player::isOnGround() {
	b2Vec2 pos = pBody->GetPosition();
	
	pos.y += ((sfShapeSize.y / 2) + 1) / SCALE;
	
	for (b2Body *it = world->GetBodyList(); it != nullptr; it = it->GetNext()) {
		for (b2Fixture *f = it->GetFixtureList(); f != nullptr; f = f->GetNext()) {
			if (f->TestPoint(pos)) {
				return true;
			}
			else if (f->TestPoint(b2Vec2(pos.x + (sfShapeSize.x / 2 / SCALE), pos.y))) {
				return true;
			}
			else if (f->TestPoint(b2Vec2(pos.x - (sfShapeSize.x / 2 / SCALE), pos.y))) {
				return true;
			}
		}
	}
	return false;
}

b2Vec2 Player::getLinearVelocity() {
	return pBody->GetLinearVelocity();
}

float32 Player::getAngle() {
	return pBody->GetAngle();
}

float32 Player::getAngularVelocity() {
	return pBody->GetAngularVelocity();
}

void Player::applyLinearImpulseToCenter(b2Vec2 imp) {
	pBody->ApplyLinearImpulseToCenter(imp, true);
}

void Player::applyForceToCenter(b2Vec2 force) {
	pBody->ApplyForceToCenter(force, true);
}

b2Vec2 Player::getPosition() {
	return pBody->GetPosition();
}

sf::Vector2f Player::getShapeSize() {
	return sfShapeSize;
}

void Player::shoot() {
	if (!coold) {
		if (udata.dir == left) {
			Bullet *bul = new Bullet(bulTex, game_, b2Vec2((getPosition().x * SCALE) - 50, (getPosition().y * SCALE)), sf::Vector2f(27.f, 25.f), 1.0f, SCALE, udata.dir);
			bList.push_back(bul);
			currentAnimation = &animation->playerAnimationShooting;
		}
		else if (udata.dir == right) {
			Bullet *bul = new Bullet(bulTex, game_, b2Vec2((getPosition().x * SCALE) + 50, (getPosition().y * SCALE)), sf::Vector2f(27.f, 26.f), 1.0f, SCALE, udata.dir);
			bList.push_back(bul);
			currentAnimation = &animation->playerAnimationShooting;
		}
		coold = true;
		shooting = true;
		if (udata.type == PLAYER_1) {
			game_->blasterSFX.play();
		}
		else if (udata.type == PLAYER_2) {
			game_->cannonSFX.play();
		}
	}
}

bool Player::isShooting() {
	return shooting;
}

objectType Player::getType() {
	return udata.type;
}

Player* Player::getObjPtr() {
	return udata.playerPtr;
}

void Player::updateCoolDown() {
	cdElapsedTime += cdClock.restart();
	if (cdElapsedTime >= cooldown) {
		cdElapsedTime = sf::Time::Zero;

		coold = false;
		shooting = false;
	}
}

bool Player::isAtCoolDown() {
	return coold;
}

void Player::handleControls() {
	b2Vec2 vel = getLinearVelocity();

	if (udata.type == PLAYER_1) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) if (vel.x < 100 / SCALE) applyLinearImpulseToCenter(b2Vec2(85, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) if (vel.x > -100 / SCALE) applyLinearImpulseToCenter(b2Vec2(-85, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) if (isOnGround()) applyLinearImpulseToCenter(b2Vec2(0, -800));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
			shoot();
		}
	}
	else if (udata.type == PLAYER_2) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) if (vel.x < 15) applyLinearImpulseToCenter(b2Vec2(300, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) if (vel.x > -15) applyLinearImpulseToCenter(b2Vec2(-300, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) if (isOnGround()) applyLinearImpulseToCenter(b2Vec2(0, -6000));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			shoot();
		}
	}
}

void Player::processBullets() {
	std::list<Bullet*>::iterator it;
	for (it = bList.begin(); it != bList.end();/**/) {
		if ((*it)->isColliding()) {

			(*it)->updateFrameTime();
			(*it)->decideAnimation();
			(*it)->playAnimation();
			(*it)->updateAnimation();
			(*it)->setDrawableState((*it)->getPosition().x * SCALE, (*it)->getPosition().y * SCALE);
			game_->draw(*((*it)->getDrawable()));

			delete (*it);
			it = bList.erase(it);
		}
		else {
			if ((*it)->getUdata().dir == left) {
				(*it)->applyLinearImpulseToCenter(b2Vec2(-3000, 0));
			}
			else if ((*it)->getUdata().dir == right) {
				(*it)->applyLinearImpulseToCenter(b2Vec2(3000, 0));
			}
			(*it)->updateFrameTime();
			(*it)->decideAnimation();
			(*it)->playAnimation();
			(*it)->updateAnimation();
			(*it)->setDrawableState((*it)->getPosition().x * SCALE, (*it)->getPosition().y * SCALE);
			game_->draw(*((*it)->getDrawable()));
			it++;
		}
	}
}

void Player::decreaseHealth() {
	health--;
}

int Player::getHealth() {
	return health;
}