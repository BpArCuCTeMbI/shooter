#ifndef UDATA_H
#define UDATA_H

class Player;
class Bullet;
class StaticRect;

enum Direction { NO_DIR, left, right };
enum objectType { NO_TYPE, PLAYER_1, PLAYER_2, STATIC_RECT, KINEMATIC_RECT, BULLET, EXPLOSION, DEBUG };

struct uData { 

	objectType type;
	Direction dir;
	
	Player* playerPtr;
	Bullet* bulletPtr;
	StaticRect* staticRectPtr;

	uData();
};

#endif