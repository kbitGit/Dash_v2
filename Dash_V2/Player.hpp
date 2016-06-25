#pragma once
#include <SFML\Graphics.hpp>
#include "Renderable.hpp"

class Player : public Renderable
{
public:
	Player(sf::Vector2<float> pos,const std::string& texture);
	void setKeys(sf::Keyboard::Key u, sf::Keyboard::Key d, sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key pOn, sf::Keyboard::Key pOff);
	~Player();
	void update(float frametime,Player &p2);
	void handle();
	void Render(sf::RenderWindow *rw);
	void position(int x, int y);
	const float getlife() { return life; };
	const float getpower() { return powerStat; };
	const bool getPStat() { return powOn; };
	const float getpositionx() { return pSprite->getPosition().x; };
	const float getpositiony() { return pSprite->getPosition().y; };
	const bool getalive() { return alive; };
	void setalive(bool alive2) { alive = alive2; };
	void setpowon(bool power) { powOn = power; };
	void setleben(float leben) { life = leben; };
	void setpower(float power) { powerStat = power; };
private:
	float life = 200;
	float powerStat = 1000;
	float speed = 10000;
	bool alive = true;
	bool powOn = false;
	std::string power;
	sf::Texture *pTexture;
	sf::Sprite  *pSprite;
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key right;
	sf::Keyboard::Key left;
	sf::Keyboard::Key powerOn;
	sf::Keyboard::Key powerOff;

};

