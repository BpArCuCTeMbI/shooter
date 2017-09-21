#include "Game.h"
#include "StaticRect.h"
#include "Player.h"

Game::Game(float scale, b2Vec2 gravity, float32 timeStep, unsigned int velIter, unsigned int posIter, std::string& musPath, std::string& sfxBlasterPath, std::string& sfxCannonPath, std::string& bgrTexPath, std::string& fontPath):SCALE(scale), gravity(gravity), timeStep(timeStep), velIter(velIter), posIter(posIter) {
	firstStarted = true;
	world = new b2World(gravity);
	gameStatus = PLAYING;
	vMode = sf::VideoMode::getDesktopMode();
	//window = new sf::RenderWindow(vMode, "Game", sf::Style::Fullscreen);
	window = new sf::RenderWindow(vMode, "Game");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);

	if (!music.openFromFile(musPath)) {
		std::cerr << "couldn't open main music" << std::endl;
	}
	music.setLoop(true);

	if (!blasterSFX.openFromFile(sfxBlasterPath)) {
		std::cerr << "couldn't open main music" << std::endl;
	}
	blasterSFX.setLoop(false);

	if (!cannonSFX.openFromFile(sfxCannonPath)) {
		std::cerr << "couldn't open main music" << std::endl;
	}
	cannonSFX.setLoop(false);

	if (!bgrTex.loadFromFile(bgrTexPath)) {
		std::cerr << "couldn't open background texture" << std::endl;
	}

	if (!font.loadFromFile(fontPath)) {
		std::cerr << "couldn't open font" << std::endl;
	}

	hp1.setFont(font);
	hp2.setFont(font);
	hp1.setCharacterSize(20);
	hp2.setCharacterSize(20);
	
	winnerText.setCharacterSize(20);
	winnerText.setFillColor(sf::Color::Black);
	winnerText.setFont(font);
	winnerText.setPosition(20, (float)vMode.height / 2);

	helpText.setCharacterSize(20);
	helpText.setFillColor(sf::Color::Black);
	helpText.setFont(font);
	helpText.setPosition(20, ((float)vMode.height / 2) + 40);

	bgrTex.setRepeated(true);
	bgr.setTextureRect(sf::IntRect(0, 0, bgrTex.getSize().x * 500, bgrTex.getSize().y * 500));
	bgr.setTexture(bgrTex);
	bgr.setOrigin(bgr.getGlobalBounds().width / 2, bgr.getGlobalBounds().height / 2);
	bgr.setPosition(0, 0);

	/*views*/
	cam1 = sf::View(sf::Vector2f((float)vMode.width / 2, (float)vMode.height / 2), sf::Vector2f((float)vMode.width / 2, (float)vMode.height));
	cam1.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.0f));
	
	cam2 = sf::View(sf::Vector2f(0, 0), sf::Vector2f((float)vMode.width / 2, (float)vMode.height));
	cam2.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.0f));

	cam3 = sf::View(sf::Vector2f(0, 0), sf::Vector2f((float)vMode.width, (float)vMode.height));
	cam3.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	
	hpBox = sf::View(sf::Vector2f((float)vMode.width / 2, (float)vMode.height / 12), sf::Vector2f((float)vMode.width, (float)vMode.height));
	hpBox.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 0.1f));
}

Game::~Game(){
	std::cout << "game destructor begins" << std::endl;
	std::list<StaticRect*>::iterator wallsIterator;
	for (wallsIterator = staticRects.begin(); wallsIterator != staticRects.end(); wallsIterator++) {
		delete (*wallsIterator);
	}
	delete world;
	delete window;
	std::cout << "game destructor finished" << std::endl;
}

void Game::computeView(b2Vec2 plPos, sf::Vector2f shapeSize, b2Vec2 pl2Pos, sf::Vector2f shape2Size) {
	if (plPos.x < pl2Pos.x) {
		cam1.setCenter(plPos.x * SCALE - shapeSize.x, plPos.y * SCALE - (shapeSize.y / 2 - 7));
		cam2.setCenter(pl2Pos.x * SCALE - shape2Size.x, pl2Pos.y * SCALE);
	}
	else if (plPos.x > pl2Pos.x) {
		cam1.setCenter(pl2Pos.x * SCALE - shape2Size.x, pl2Pos.y * SCALE);
		cam2.setCenter(plPos.x * SCALE - shapeSize.x, plPos.y * SCALE - (shapeSize.y / 2 - 7));
	}
	cam3.setCenter((plPos.x * SCALE + pl2Pos.x * SCALE) / 2, (plPos.y * SCALE + pl2Pos.y *SCALE) / 2);
}

void Game::setContactListener(b2ContactListener* listener) {
	world->SetContactListener(listener);
}

void Game::processStatics() {
	std::list<StaticRect*>::iterator staticsIterator;
	for (staticsIterator = staticRects.begin(); staticsIterator != staticRects.end(); staticsIterator++) {
		(*staticsIterator)->setDrawableState((*staticsIterator)->getPosition().x*SCALE, (*staticsIterator)->getPosition().y*SCALE, (*staticsIterator)->getAngle() * 180 / b2_pi);
		//window->draw(*(*staticsIterator)->getDrawable());
	}
}

void Game::processDynamicBodies() {
	Player* pl;
	for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != nullptr; BodyIterator = BodyIterator->GetNext()) {
		if (((uData*)BodyIterator->GetUserData())->type == PLAYER_1) {
			pl = ((uData*)BodyIterator->GetUserData())->playerPtr;

			pl->handleControls();
			pl->decideAnimation();

			pl->setDrawableState(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE, BodyIterator->GetAngle() * 180 / b2_pi);
			pl->processBullets();

		}
		else if (((uData*)BodyIterator->GetUserData())->type == PLAYER_2) {
			pl = ((uData*)BodyIterator->GetUserData())->playerPtr;

			pl->handleControls();
			pl->decideAnimation();

			pl->setDrawableState(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE, BodyIterator->GetAngle() * 180 / b2_pi);
			pl->processBullets();

		}
	}
}

void Game::draw(sf::Drawable& drawable) {
	window->draw(drawable);
}

void Game::checkHealth(Player& player1, Player& player2) {
	if (player1.getHealth() <= 0) {
		gameStatus = PLAYER_TWO_WON;
	}
	else if (player2.getHealth() <= 0) {
		gameStatus = PLAYER_ONE_WON;
	}
	else {
		gameStatus = PLAYING;
	}
}

void Game::drawHUD(int health1, int health2) {
	hp1.setString("PLAYER1: " + std::to_string(health1) + "HP");
	hp2.setString("PLAYER2: " + std::to_string(health2) + "HP");
	/*
	if (pl1Pos.x < pl2Pos.x) {
		hp1.setPosition(cam1.getCenter().x, cam1.getCenter().y - 20);
		hp2.setPosition(cam2.getCenter().x, cam2.getCenter().y - 20);
	}
	else if (pl1Pos.x > pl2Pos.x) {
		hp1.setPosition(cam2.getCenter().x, cam2.getCenter().y - 20);
		hp2.setPosition(cam1.getCenter().x, cam1.getCenter().y - 20);
	}
	*/

	hp1.setPosition(20, 20);
	hp2.setPosition(vMode.width * 0.81, 20);

	window->draw(hp1);
	window->draw(hp2);
}

bool Game::isFinished() {
	if (gameStatus == PLAYING) {
		return false;
	}
	else {
		return true;
	}
}

void Game::drawFinishScreen() {
	if (gameStatus == PLAYER_ONE_WON) {
		winnerText.setString("Congratulations, PLAYER1 is a WINNER!");
		std::cout << "player1 won" << std::endl;
	}
	else if (gameStatus == PLAYER_TWO_WON) {
		winnerText.setString("Congratulations, PLAYER2 is a WINNER!");
		std::cout << "player2 won" << std::endl;
	}

	helpText.setString("R - to restart; ESC - to EXIT");
	window->draw(helpText);
	window->draw(winnerText);
}

void Game::restart(Player& player1, Player& player2) {
	gameStatus = GameStatus::PLAYING;
	delete &player1;
	delete &player2;
}

void Game::drawControlsInfo() {
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time time = sf::seconds(7);

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setString("CONTROLS:");
	text.setPosition((float)vMode.width / 4, (float)vMode.height / 3);

	sf::Text controlsText1;
	controlsText1.setFont(font);
	controlsText1.setCharacterSize(30);
	controlsText1.setString("P1: WASD + F");
	controlsText1.setPosition((float)vMode.width / 4, (float)vMode.height / 2);

	sf::Text controlsText2;
	controlsText2.setFont(font);
	controlsText2.setCharacterSize(30);
	controlsText2.setString("P2: ARROWS + RControl");
	controlsText2.setPosition((float)vMode.width / 4, ((float)vMode.height / 2) + 40);

	while (window->isOpen()) {
		elapsedTime += clock.restart();
		if (elapsedTime >= time) {
			break;
		}

		sf::Event event;
		while (window->pollEvent(event)) {

			switch (event.type) {

			case sf::Event::Closed: {
				window->close();
				break;
			}

			case sf::Event::Resized: {
				sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
				window->setView(sf::View(visibleArea));
				break;
			}

			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape) {
					window->close();
				}
			}
			}
		}

		window->clear(sf::Color(3, 46, 63, 255));

		window->draw(text);
		window->draw(controlsText1);
		window->draw(controlsText2);

		window->display();
	}
	firstStarted = false;
}

void Game::drawDrawableContainer(DrawableContainer& drwContainer) {
	if (drwContainer.drwType == DrawableType::TEXTURED) {
		draw(*drwContainer.spr);
	}
	else {
		draw(*drwContainer.rShape);
	}
}

void Game::createTexturedStaticRect(Game& game, sf::Vector2i& size, sf::Vector2f& position, float32 friction, const float32& SCALE, float32 angVel, const std::string& texPath) {
	StaticRect* rectPtr = new StaticRect(game, size, position, 0.6f, SCALE, 0, texPath);
	staticRects.push_back(rectPtr);
}

void Game::createUntexturedStaticRect(Game &game, sf::Vector2f& size, sf::Color fillColor, sf::Vector2f& position, float32 friction, const float32 &SCALE, float32 angVel) {
	StaticRect* rectPtr = new StaticRect(game, size, fillColor, position, 0.6f, SCALE, angVel);
	staticRects.push_back(rectPtr);
}

void Game::doStep() {
	world->Step(timeStep, velIter, posIter);
}