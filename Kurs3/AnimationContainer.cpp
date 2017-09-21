#include "AnimationContainer.h"

AnimationContainer::AnimationContainer(sf::Texture &texture, objectType objType) {
	if (objType == PLAYER_1) {
		/*idling*/
		playerAnimationIdling.setSpriteSheet(texture);
		playerAnimationIdling.addFrame(sf::IntRect(4, 2, 30, 38));
		playerAnimationIdling.addFrame(sf::IntRect(35, 2, 29, 38));
		playerAnimationIdling.addFrame(sf::IntRect(64, 2, 29, 38));

		/*other animations*/
		playerAnimationMoving.setSpriteSheet(texture);
		playerAnimationMoving.addFrame(sf::IntRect(107, 2, 30, 40));
		playerAnimationMoving.addFrame(sf::IntRect(139, 1, 28, 41));
		playerAnimationMoving.addFrame(sf::IntRect(168, 1, 32, 40));
		playerAnimationMoving.addFrame(sf::IntRect(201, 1, 32, 41));
		playerAnimationMoving.addFrame(sf::IntRect(235, 1, 27, 40));
		playerAnimationMoving.addFrame(sf::IntRect(266, 1, 29, 40));
		playerAnimationMoving.addFrame(sf::IntRect(298, 1, 32, 40));
		playerAnimationMoving.addFrame(sf::IntRect(330, 1, 36, 37));
		playerAnimationMoving.addFrame(sf::IntRect(366, 1, 31, 40));

		playerAnimationJumping.setSpriteSheet(texture);
		playerAnimationJumping.addFrame(sf::IntRect(3, 189, 29, 48));
		playerAnimationJumping.addFrame(sf::IntRect(32, 190, 29, 46));
		playerAnimationJumping.addFrame(sf::IntRect(63, 191, 29, 44));
		playerAnimationJumping.addFrame(sf::IntRect(94, 192, 29, 41));
		playerAnimationJumping.addFrame(sf::IntRect(124, 193, 29, 37));
		playerAnimationJumping.addFrame(sf::IntRect(156, 193, 29, 36));
		playerAnimationJumping.addFrame(sf::IntRect(187, 193, 29, 37));
		playerAnimationJumping.addFrame(sf::IntRect(218, 193, 29, 41));
		playerAnimationJumping.addFrame(sf::IntRect(250, 192, 29, 44));
		//playerAnimationJumping.addFrame(sf::IntRect(280, 195, 29, 37));
		//playerAnimationJumping.addFrame(sf::IntRect(309, 195, 29, 36));
		//playerAnimationJumping.addFrame(sf::IntRect(338, 194, 30, 37));
		//playerAnimationJumping.addFrame(sf::IntRect(368, 194, 32, 37));

		playerAnimationShooting.setSpriteSheet(texture);
		playerAnimationShooting.addFrame(sf::IntRect(3, 59, 50, 37));
		playerAnimationShooting.addFrame(sf::IntRect(55, 59, 51, 37));
		playerAnimationShooting.addFrame(sf::IntRect(110, 59, 37, 37));
		playerAnimationShooting.addFrame(sf::IntRect(152, 57, 37, 39));
		playerAnimationShooting.addFrame(sf::IntRect(192, 58, 32, 38));

	}
	else if(objType == PLAYER_2) {
		player2AnimationIdling.setSpriteSheet(texture);
		player2AnimationIdling.addFrame(sf::IntRect(6, 6, 64, 62));
		player2AnimationIdling.addFrame(sf::IntRect(73, 6, 64, 62));
		player2AnimationIdling.addFrame(sf::IntRect(140, 6, 64, 62));
		player2AnimationIdling.addFrame(sf::IntRect(207, 6, 64, 62));

		player2AnimationJumping.setSpriteSheet(texture);
		player2AnimationJumping.addFrame(sf::IntRect(6, 609, 64, 82));
		player2AnimationJumping.addFrame(sf::IntRect(73, 609, 64, 77));
		player2AnimationJumping.addFrame(sf::IntRect(140, 609, 64, 75));
		player2AnimationJumping.addFrame(sf::IntRect(207, 609, 64, 71));
		player2AnimationJumping.addFrame(sf::IntRect(274, 609, 64, 68));
		player2AnimationJumping.addFrame(sf::IntRect(341, 609, 64, 67));
		player2AnimationJumping.addFrame(sf::IntRect(408, 609, 64, 66));

		player2AnimationMoving.setSpriteSheet(texture);
		player2AnimationMoving.addFrame(sf::IntRect(6, 74, 64, 63));
		player2AnimationMoving.addFrame(sf::IntRect(73, 75, 64, 62));
		player2AnimationMoving.addFrame(sf::IntRect(140, 75, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(209, 75, 64, 62));
		player2AnimationMoving.addFrame(sf::IntRect(277, 75, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(346, 75, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(415, 75, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(6, 143, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(75, 142, 66, 63));
		player2AnimationMoving.addFrame(sf::IntRect(144, 143, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(213, 143, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(282, 143, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(351, 143, 65, 62));
		player2AnimationMoving.addFrame(sf::IntRect(419, 143, 66, 62));
		player2AnimationMoving.addFrame(sf::IntRect(6, 210, 64, 62));
		player2AnimationMoving.addFrame(sf::IntRect(73, 210, 64, 62));

		player2AnimationShooting.setSpriteSheet(texture);
		player2AnimationShooting.addFrame(sf::IntRect(379, 1280, 72, 62));
		player2AnimationShooting.addFrame(sf::IntRect(302, 1280, 74, 62));
		player2AnimationShooting.addFrame(sf::IntRect(228, 1280, 71, 62));


	}
	else if (objType == BULLET) {
		bulletAnimationMoving.setSpriteSheet(texture);
		bulletAnimationMoving.addFrame(sf::IntRect(3, 11, 27, 11));
		bulletAnimationMoving.addFrame(sf::IntRect(36, 11, 27, 11));
		bulletAnimationMoving.addFrame(sf::IntRect(67, 12, 28, 11));
		bulletAnimationMoving.addFrame(sf::IntRect(100, 12, 27, 12));

		bulletAnimationHit.setSpriteSheet(texture);
		bulletAnimationHit.addFrame(sf::IntRect(134, 6, 24, 24));
		bulletAnimationHit.addFrame(sf::IntRect(168, 4, 22, 25));
		bulletAnimationHit.addFrame(sf::IntRect(207, 12, 15, 12));
	}
	else if (objType == EXPLOSION) {
		explosion.setSpriteSheet(texture);
		explosion.addFrame(sf::IntRect(349, 235, 34, 70));
		explosion.addFrame(sf::IntRect(5, 303, 41, 97));
		explosion.addFrame(sf::IntRect(54, 306, 47, 96));
		explosion.addFrame(sf::IntRect(110, 305, 47, 97));
		explosion.addFrame(sf::IntRect(166, 305, 48, 98));
		explosion.addFrame(sf::IntRect(223, 306, 48, 98));
		explosion.addFrame(sf::IntRect(281, 307, 47, 99));
		explosion.addFrame(sf::IntRect(335, 309, 48, 100));
		explosion.addFrame(sf::IntRect(3, 405, 47, 101));
		explosion.addFrame(sf::IntRect(53, 407, 47, 99));
		explosion.addFrame(sf::IntRect(102, 410, 48, 92));
		explosion.addFrame(sf::IntRect(152, 411, 48, 86));
		explosion.addFrame(sf::IntRect(202, 411, 48, 81));
		explosion.addFrame(sf::IntRect(252, 411, 48, 82));
		explosion.addFrame(sf::IntRect(302, 411, 48, 80));
		explosion.addFrame(sf::IntRect(351, 412, 48, 75));
	}
}

AnimationContainer::~AnimationContainer() {

}
