#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "AnimatedSprite.hpp"
#include <SFML\Audio\Music.hpp>
#include <iostream>
#include <list>
#include "GameStatus.h"
#include "DrawableContainer.h"

/*forward declaration to prevent cyclic dependency*/
class StaticRect;
class Player;

class Game {
public:
	const float SCALE;
	
	b2Vec2 gravity;
	b2World* world;

	float32 timeStep; 
	unsigned int velIter;
	unsigned int posIter;

	sf::VideoMode vMode;
	sf::RenderWindow* window;
	
	sf::Sprite bgr;
	sf::Texture bgrTex;

	sf::Text hp1;
	sf::Text hp2;

	sf::Text winnerText;
	sf::Text helpText;

	sf::Font font;

	sf::Music music;
	sf::Music blasterSFX;
	sf::Music cannonSFX;

	sf::View cam1;
	sf::View cam2;
	sf::View cam3;
	sf::View hpBox;

	GameStatus gameStatus;

	bool firstStarted;

	std::list<StaticRect*> staticRects;

public:

	Game(float scale, b2Vec2 gravity, float32 timeStep, unsigned int velIter, unsigned int posIter, std::string& musPath, std::string& sfxBlasterPath, std::string& sfxCannonPath, std::string& bgrTexPath, std::string& fontPath);
	~Game();

	void computeView(b2Vec2 plPos, sf::Vector2f shapeSize, b2Vec2 pl2Pos, sf::Vector2f shape2Size);

	void setContactListener(b2ContactListener* listener);
	void processStatics();
	void processDynamicBodies();

	void draw(sf::Drawable& drawable);

	void checkHealth(Player& player1, Player& player2);

	void drawHUD(int health1, int health2);
	void drawFinishScreen();

	bool isFinished();

	void doStep();

	void restart(Player& player1, Player& player2);

	void drawControlsInfo();
	void drawDrawableContainer(DrawableContainer& drwContainer);

	void createTexturedStaticRect(Game& game, sf::Vector2i& size, sf::Vector2f& position, float32 friction, const float32& SCALE, float32 angVel, const std::string& texPath);
	void createUntexturedStaticRect(Game &game, sf::Vector2f& size, sf::Color fillColor, sf::Vector2f& position, float32 friction, const float32 &SCALE, float32 angVel);
};

#endif
