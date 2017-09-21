#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Box2D\Box2D.h"
#include "UData.h"
#include "Bullet.h"
#include "Player.h"

class ContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact);
	//void EndContact(b2Contact* contact);
	//void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif