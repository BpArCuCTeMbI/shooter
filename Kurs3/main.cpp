#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <AnimatedSprite.hpp>
#include "Player.h"
#include "StaticRect.h"
#include "Game.h"
#include "ContactListener.h"
#include <cmath>

int main()
{
	//////////////////////////////////////////////
	const float32 SCALE = 6.0;
	b2Vec2 gravity(0.0f, 9.8f);
	
	float32 timeStep = 1 / 15.f;
	unsigned int velIter = 8;
	unsigned int posIter = 3;

	ContactListener cListener;
	/////////////////////////////////////////////////////////////////////////////

	std::string musPath = "../resources/music/boss.ogg";
	std::string sfxBlasterPath = "../resources/music/sfxShot1.ogg";
	std::string sfxCannonPath = "../resources/music/sfxShot2.ogg";
	std::string tPath = "../resources/textures/ms_player.png";
	std::string p2Path = "../resources/textures/ms_gunner.png";
	std::string bulTexPath = "../resources/textures/shoots.png";
	std::string bgrTexPath = "../resources/textures/bgr1.jpg";
	//std::string explTexPath = "../resources/textures/ms_player.png";
	std::string font1Path = "../resources/fonts/font1.ttf";
	std::string font2Path = "../resources/fonts/font2.ttf";
	std::string grTexPath = "../resources/textures/gr_top.png";
	/////////////////////////////////////////////////////////////////////////////
	/*
	sf::Texture* explosionTex = new sf::Texture();
	if (!explosionTex->loadFromFile(explTexPath)) {
		std::cerr << "failed to load explosion texture" << std::endl;
	}

	AnimatedSprite* explSpr;
	Animation* currentAnimation;
	AnimationContainer* animation;
	sf::Clock frameClock;
	sf::Time frameTime;

	animation = new AnimationContainer(*explosionTex, objectType::EXPLOSION);
	currentAnimation = &animation->explosion;
	explSpr = new AnimatedSprite(sf::seconds(0.1f), true, false);
	explSpr->setOrigin(sf::Vector2f(48 / 2, 101 / 2));
	*/
	////////////////////////////////////////////////////////////////////////////
	Game game(SCALE, gravity, timeStep, velIter, posIter, musPath, sfxBlasterPath, sfxCannonPath, bgrTexPath, font1Path);
	game.setContactListener(&cListener);

	sf::Vector2i gndSize1(1920*100, 250);
	sf::Vector2f wallSize(150, 30);
	sf::Vector2f wallPos(15, 830);
	
	game.createUntexturedStaticRect(game, wallSize, sf::Color(94, 0, 16, 255), sf::Vector2f(20, 350), 0.6f, SCALE, 30);

	game.createTexturedStaticRect(game, gndSize1, sf::Vector2f(0, 850), 0.6f, SCALE, 0, grTexPath);
	
	for (int i = 0; i < 15; i++) {
		game.createUntexturedStaticRect(game, wallSize, sf::Color::Cyan, wallPos, 0.6f, SCALE, 0);

		wallPos.x += 120;
		wallPos.y -= 120;
	}

	wallPos = sf::Vector2f(10, 830);
	for (int i = 0; i < 15; i++) {
		game.createUntexturedStaticRect(game, wallSize, sf::Color(32, 6, 68, 255), wallPos, 0.6f, SCALE, 0);

		wallPos.x -= 120;
		wallPos.y -= 120;
	}

	if (game.firstStarted) {
		game.drawControlsInfo();
	}

	game.music.play();

GameStart:
	Player* pl = new Player(tPath, game, b2Vec2(20.f, 30.f), sf::Vector2f(30, 38), 1.0f, 0.8f, PLAYER_1, bulTexPath);
	Player* pl2 = new Player(p2Path, game, b2Vec2(100.f, 100.f), sf::Vector2f(64, 62), 2.0f, 0.8f, PLAYER_2, bulTexPath);

	Player& player = *pl;
	Player& player2 = *pl2;

	/*main loop*/
	while (game.window->isOpen() && !game.isFinished()){
		
		//game.world->Step(game.timeStep, game.velIter, game.posIter);
		game.doStep();
		game.window->clear();

		player.updateCoolDown();
		player.updateFrameTime();
		player.updateAnimation();
		player.playAnimation();

		player2.updateCoolDown();
		player2.updateFrameTime();
		player2.updateAnimation();
		player2.playAnimation();

		sf::Event event;
		while (game.window->pollEvent(event)) {

			switch (event.type) {

			case sf::Event::Closed: {
				game.window->close();
				break;
			}
			
			case sf::Event::Resized: {
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
				game.window->setView(sf::View(visibleArea));
				break;
			}
			
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape) {
					game.window->close();
				}
			}
			}
		}


		game.computeView(player.getPosition(), player.getShapeSize(), player2.getPosition(), player2.getShapeSize());
		
		if ((abs(player.getPosition().x * SCALE - player2.getPosition().x * SCALE) <= game.vMode.width) && (abs(player.getPosition().y * SCALE - player2.getPosition().y * SCALE) <= game.vMode.height)) {
			game.window->setView(game.cam3);

			game.draw(game.bgr);
			game.processStatics();
			game.processDynamicBodies();

			game.draw(*player.getDrawable());
			game.draw(*player2.getDrawable());
			std::list<StaticRect*>::iterator staticsIterator;
			for (staticsIterator = game.staticRects.begin(); staticsIterator != game.staticRects.end(); staticsIterator++) {
				game.drawDrawableContainer((*staticsIterator)->getDrawableContainer());
			}

			//game.drawHP(player.getHealth(), player2.getHealth(), player.getPosition(), player2.getPosition(), 0);

		}
		else {
			game.processStatics();
			////////////////////////////////////
			game.window->setView(game.cam1);

			game.draw(game.bgr);
			game.processDynamicBodies();
			game.draw(*player.getDrawable());
			game.draw(*player2.getDrawable());

			std::list<StaticRect*>::iterator staticsIterator;
			for (staticsIterator = game.staticRects.begin(); staticsIterator != game.staticRects.end(); staticsIterator++) {
				game.drawDrawableContainer((*staticsIterator)->getDrawableContainer());
			}

			//game.drawHP(player.getHealth(), player2.getHealth(), player.getPosition(), player2.getPosition(), 1);
			///////////////////////////////////
			game.window->setView(game.cam2);

			game.draw(game.bgr);

			game.processDynamicBodies();
			game.draw(*player.getDrawable());
			game.draw(*player2.getDrawable());

			for (staticsIterator = game.staticRects.begin(); staticsIterator != game.staticRects.end(); staticsIterator++) {
				game.drawDrawableContainer((*staticsIterator)->getDrawableContainer());
			}
	
			//game.drawHP(player.getHealth(), player2.getHealth(), player.getPosition(), player2.getPosition(), 1);
		}

		game.checkHealth(player, player2);
		/////////////////////////////////////////////////
		game.window->setView(game.window->getDefaultView());
		game.drawHUD(player.getHealth(), player2.getHealth());
		/////////////////////////////////////////////////////
		/*
		if (game.isFinished()) {
			if (game.gameStatus == PLAYER_ONE_WON) {
				std::cout << "PLAYER 1 WON" << std::endl;
				sf::Vector2f pos(player2.getPosition().x * SCALE, player2.getPosition().y * SCALE);
				//explSpr->setPosition(pos);
				if (player.getPosition().x < player2.getPosition().x) {
					explSpr->setPosition(game.cam2.getCenter().x + 60, game.cam2.getCenter().y);
				}
				else if (player.getPosition().x > player2.getPosition().x) {
					explSpr->setPosition(game.cam1.getCenter().x + 60, game.cam1.getCenter().y);
				}

				frameTime = frameClock.restart();
				explSpr->update(frameTime);
				explSpr->play(*currentAnimation);

				game.window->draw(*explSpr);
			}

			if (game.gameStatus == PLAYER_TWO_WON) {
				std::cout << "PLAYER 2 WON" << std::endl;
				sf::Vector2f pos(player.getPosition().x * SCALE, player.getPosition().y * SCALE);
				if (player.getPosition().x < player2.getPosition().x) {
					explSpr->setPosition(game.cam2.getCenter().x, game.cam2.getCenter().y);
				}
				else if (player.getPosition().x > player2.getPosition().x) {
					explSpr->setPosition(game.cam1.getCenter().x, game.cam1.getCenter().y);
				}
				frameTime = frameClock.restart();
				explSpr->update(frameTime);
				explSpr->play(*currentAnimation);

				game.window->draw(*explSpr);
			}
		}*/
		game.window->display();

	}

	/*winner loop*/
	while (game.window->isOpen()) {
		
		game.window->clear(sf::Color(0, 67, 42, 255));

		sf::Event event;
		while (game.window->pollEvent(event)) {

			switch (event.type) {

				case sf::Event::Closed: {
					game.window->close();
					break;
				}

				case sf::Event::Resized: {
					// update the current view to the new size of the window
					sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
					game.window->setView(sf::View(visibleArea));
					break;
				}

				case sf::Event::KeyPressed: {
					if (event.key.code == sf::Keyboard::Escape) {
						game.window->close();
					}
					else if (event.key.code == sf::Keyboard::R) {
						game.restart(player, player2);
						goto GameStart;
					}
				}
			}
		}

		game.window->setView(game.window->getDefaultView());

		game.drawFinishScreen();
		game.window->display();
	}

	delete pl;
	delete pl2;
	return 0;
}