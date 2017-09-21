#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact) {
	uData* bodyDataA;
	uData* bodyDataB;
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyUserDataA != nullptr && bodyUserDataB != nullptr) {

		bodyDataA = static_cast<uData*>(bodyUserDataA);
		bodyDataB = static_cast<uData*>(bodyUserDataB);
		
		if ((bodyDataB->type == BULLET && bodyDataA->type == BULLET) || (bodyDataA->type == BULLET && bodyDataB->type == BULLET)) {
			static_cast<Bullet*>(bodyDataB->bulletPtr)->startContact();
			static_cast<Bullet*>(bodyDataA->bulletPtr)->startContact();
			std::cout << "bullets collision" << std::endl;
		}
		else if ((bodyDataA->type == BULLET) && (bodyDataB->type != PLAYER_1) && (bodyDataB->type != PLAYER_2)) {
			static_cast<Bullet*>(bodyDataA->bulletPtr)->startContact();
			std::cout << "non-player hit" << std::endl;
		}
		else if ((bodyDataB->type == BULLET) && (bodyDataA->type != PLAYER_1) && (bodyDataA->type != PLAYER_2)) {
			static_cast<Bullet*>(bodyDataB->bulletPtr)->startContact();
			std::cout << "non-player hit" << std::endl;
		}
		else if ((bodyDataA->type == BULLET) && (bodyDataB->type == PLAYER_1 || bodyDataB->type == PLAYER_2)) {
			static_cast<Bullet*>(bodyDataA->bulletPtr)->startContact();
			static_cast<Player*>(bodyDataB->playerPtr)->decreaseHealth();
			std::cout << "Player hit" << std::endl;
		}
		else if (bodyDataB->type == BULLET && (bodyDataA->type == PLAYER_1 || bodyDataA->type == PLAYER_2)) {
			static_cast<Bullet*>(bodyDataB->bulletPtr)->startContact();
			static_cast<Player*>(bodyDataA->playerPtr)->decreaseHealth();
			std::cout << "Player hit" << std::endl;
		}
		/*other decisions*/
	}
	else {
		std::cerr << "err: contact listener: bodyUserDataA or bodyUserDataB is NULL" << std::endl;
	}
	
}