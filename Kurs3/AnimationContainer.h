#ifndef ANIMATIONCONTAINER_H
#define ANIMATIONCONTAINER_H

#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "UData.h"

class AnimationContainer {
public:
	Animation playerAnimationIdling;
	Animation playerAnimationMoving;
	Animation playerAnimationJumping;
	Animation playerAnimationShooting;

	Animation player2AnimationIdling;
	Animation player2AnimationMoving;
	Animation player2AnimationJumping;
	Animation player2AnimationShooting;

	Animation bulletAnimationMoving;
	Animation bulletAnimationHit;

	Animation explosion;


public:
	AnimationContainer(sf::Texture &texture, objectType objType);
	~AnimationContainer();

};

#endif
