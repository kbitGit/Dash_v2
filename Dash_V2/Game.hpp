#pragma once
#include <SFML\Audio.hpp>
#include "Application.hpp"
#include "Scenes.hpp"
#include "Player.hpp"
#include "Collision.hpp"
#include <memory>
#include <iostream>
#include <functional>
#define SCALE 2.5f
typedef std::function<void(Scenes &scene)> CallBack;
typedef std::function<void(const sf::View& view)> CallBackView;

class spriteSplash : public Renderable {
public:
	void Render(sf::RenderWindow * rw) {
		rw->draw(*sprite);
	}
	spriteSplash() {
		sprite = new sf::Sprite();
		text = new sf::Texture();
		sf::Image im;
		im.loadFromFile("Splashscreen.png");
		im.createMaskFromColor(sf::Color::White);

		text->loadFromImage(im);
		sprite->setTexture(*text);
	}
	~spriteSplash() {
		delete sprite;
		delete text;

		sprite = nullptr;
		text = nullptr;
	}
private:
	sf::Sprite *sprite;
	sf::Texture *text;

};

class backGround : public Renderable {
public:
	backGround(float width, float height) {
		test = new sf::Texture;
		backGroundSp = new sf::Sprite();
		sf::Image im;
		im.loadFromFile("Arena_highres.png");
		im.createMaskFromColor(sf::Color::White);
		test->loadFromImage(im);
		backGroundSp->setTexture(*test);
		backGroundSp->scale(width / test->getSize().x, height / test->getSize().y - (5 * test->getSize().y) / 100);

	}
	~backGround() {
		delete backGroundSp;
		delete test;

		test = nullptr;
		backGroundSp = nullptr;
	}
	float getTextureY() {
		return test->getSize().y;
	}
	void Render(sf::RenderWindow * rw)
	{
		rw->draw(*backGroundSp);
	}
private:
	sf::Texture* test;
	sf::Sprite *backGroundSp;

};

class endScreen : public Scenes {
public:
	endScreen(const std::string& winner, sf::Vector2f position) {
		font = new sf::Font();
		text = new uiText(font, position);

		font->loadFromFile("Simpleman.ttf");
		text->setText(winner + " wins the Game!");
		addToRender(*text);

	}
	~endScreen() {
		delete text;
		delete font;

		text = nullptr;
		font = nullptr;
	}
	void Update(float&frameTime) {

	}
	void Handle(sf::Event *mainEvent) {

	}
private:
	uiText* text;
	sf::Font* font;
};

class gamePlayScene : public Scenes {

public:
	gamePlayScene(float width, float height, CallBack t, CallBackView viewChange) {
		changeScene = t;
		changeView = viewChange;
		uiFont = new sf::Font();
		uiFont->loadFromFile("Simpleman.ttf");
		playerRedStatus = new uiText(uiFont, sf::Vector2f(10, -40));
		playerBlueStatus = new uiText(uiFont, sf::Vector2f(width / 2, -40));

		playerRed = new Player(sf::Vector2<float>(20, 20), "Player_red.png");
		playerBlue = new Player(sf::Vector2<float>(1260 - 32 * 2.5f, 20), "Player_blue.png");
		back = new backGround(width, height);

		playerRed->setKeys(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::C, sf::Keyboard::V);
		playerBlue->setKeys(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RShift, sf::Keyboard::RControl);


		std::string blue = "Leben: " + std::to_string(int(playerBlue->getlife())) + " Power: " + std::to_string(int(playerBlue->getpower())) + " Power on:" + std::to_string(playerBlue->getPStat());
		playerBlueStatus->setText(blue);
		std::string red = "Leben: " + std::to_string(int(playerRed->getlife())) + " Power: " + std::to_string(int(playerRed->getpower())) + " Power on:" + std::to_string(playerRed->getPStat());
		playerRedStatus->setText(red);


		addToRender(*back);
		addToRender(*playerRed);
		addToRender(*playerBlue);
		addToRender(*playerBlueStatus);
		addToRender(*playerRedStatus);
		sf::View view(sf::Vector2<float>(width / 2, height / 2 - (175 * (this->getBack().getTextureY())) / 100), sf::Vector2<float>(width, height));
		viewChange(view);
		gameMusic = new sf::Music();
		gameMusic->openFromFile("gameMusic.ogg");
		gameMusic->setLoop(true);
		gameMusic->play();

	}
	~gamePlayScene() {
		delete playerRedStatus;
		delete playerBlueStatus;
		delete uiFont;

		delete back;
		delete playerRed;
		delete playerBlue;
		gameMusic->stop();
		if (gameMusic->Stopped)
		{
			delete gameMusic;
			gameMusic = nullptr;
		}

		back = nullptr;
		playerRed = nullptr;
		playerBlue = nullptr;
		uiFont = nullptr;

		playerRedStatus = nullptr;
		playerBlueStatus = nullptr;

	}
	backGround& getBack() {
		return *back;
	}
	void Update(float& frameTime) {
		playerRed->update(frameTime, *playerBlue);
		playerBlue->update(frameTime, *playerRed);
		if (playerBlue->getalive())
		{
			playerBlueStatus->setText("Leben: " + std::to_string(int(playerBlue->getlife())) + " Power: " + std::to_string(int(playerBlue->getpower())) + " Power on:" + std::to_string(playerBlue->getPStat()));

		}
		if (playerRed->getalive())
		{
			playerRedStatus->setText("Leben: " + std::to_string(int(playerRed->getlife())) + " Power: " + std::to_string(int(playerRed->getpower())) + " Power on:" + std::to_string(playerRed->getPStat()));
		}

		if (Collision::colliding(*playerBlue, *playerRed, frameTime)) {

			if (playerBlue->getPStat() && playerBlue->getpower() > 0 && !playerRed->getPStat()) {
				playerRed->setleben(playerRed->getlife() - 75 * frameTime);
				playerBlue->setpower(playerBlue->getpower() - 1000 * frameTime);
			}
			if (!playerBlue->getPStat() && playerRed->getPStat() && playerRed->getpower() > 0) {
				playerBlue->setleben(playerBlue->getlife() - 75 * frameTime);
				playerRed->setpower(playerRed->getpower() - 1000 * frameTime);

			}
			if (playerBlue->getPStat() && playerBlue->getpower() > 0 && playerRed->getPStat() && playerRed->getpower() > 0) {
				playerRed->setleben(playerRed->getlife() - 200 * frameTime);
				playerBlue->setleben(playerBlue->getlife() - 200 * frameTime);
				playerRed->setpower(playerRed->getpower() - 10000 * frameTime);
				playerBlue->setpower(playerBlue->getpower() - 10000 * frameTime);
			}
			if (playerRed->getpower() <= 0) {
				playerRed->setpowon(false);
			}
			if (playerBlue->getpower() <= 0) {
				playerBlue->setpowon(false);
			}
			if (playerBlue->getlife() <= 0)
				changeScene(*new endScreen("RedPlayer", sf::Vector2f(1280 / 2 - 200, 720 / 2 - 75)));


			if (playerRed->getlife() <= 0)
				changeScene(*new endScreen("BluePlayer", sf::Vector2f(1280 / 2 - 200, 720 / 2 - 75)));

		}

	}
	void Handle(sf::Event *mainEvent) {
		playerRed->handle();
		playerBlue->handle();
	}
private:
	sf::Font* uiFont;
	sf::Music* gameMusic;
	uiText* playerRedStatus;
	uiText* playerBlueStatus;
	Player *playerRed;
	Player *playerBlue;
	backGround *back;
	CallBack changeScene;
	CallBackView changeView;
};

class Splashscreen : public Scenes
{
public:
	Splashscreen(float width, float height, CallBack sceneChange, CallBackView vc) {
		viewChangeCB = vc;
		sceneChangeCB = sceneChange;
		splash = new spriteSplash();
		addToRender(*splash);
		showTimeSplash = new sf::Clock();
		size = new sf::Vector2f(width, height);
	}
	~Splashscreen() {
		delete splash;
		delete showTimeSplash;
		delete size;

		splash = nullptr;
		showTimeSplash = nullptr;
		size = nullptr;
	}
	void Update(float&frameTime) {
		if (showTimeSplash->getElapsedTime().asSeconds() >= 10 || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			sceneChangeCB(*new gamePlayScene(size->x, size->y, sceneChangeCB, viewChangeCB));
		}
	}
	void Handle(sf::Event *mainEvent) {

	}
private:
	sf::Vector2f *size;
	sf::Clock *showTimeSplash;
	spriteSplash* splash;
	CallBack sceneChangeCB;
	CallBackView viewChangeCB;

};

class Game :public Application
{
public:

	Game(const std::string& title, int width, int height);
	~Game();
private:
	void initGame(int width, int height);
	Splashscreen *startScene;

};

