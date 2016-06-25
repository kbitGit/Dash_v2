#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Player::Player(sf::Vector2<float> pos, const std::string& texture)
{
	pTexture = new sf::Texture();
	pSprite = new sf::Sprite();
	sf::Image im;
	im.loadFromFile(texture);
	im.createMaskFromColor(sf::Color::White);

	pTexture->loadFromImage(im);
	pSprite->setTexture(*pTexture);
	pSprite->setPosition(pos);
	pSprite->scale(SCALE, SCALE);

}

void Player::setKeys(sf::Keyboard::Key u, sf::Keyboard::Key d, sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key pOn, sf::Keyboard::Key pOff)
{
	up = u;
	down = d;
	right = r;
	left = l;
	powerOn = pOn;
	powerOff = pOff;
}


Player::~Player()
{
	if (pTexture != nullptr)
	{
		delete pTexture;
		pTexture = nullptr;
	}
	if (pSprite != nullptr)
	{
		delete pSprite;
		pSprite = nullptr;
	}
}

void Player::update(float frametime, Player& p2)
{

	auto movement = 10 * speed*frametime;

	if (sf::Keyboard::isKeyPressed(up)
		&& !Collision::collisionUpBorder(*this, sf::Vector2<float>(1280, 720 - (175 * 32) / 100)))
	{
		if (!Collision::topcolliding(*this, p2, movement))
			pSprite->move(0, -movement);
	}
	if (sf::Keyboard::isKeyPressed(down)
		&& !Collision::collisionLowBorder(*this, sf::Vector2<float>(1280, 720 - (175 * 32) / 100)))
	{
		if (!Collision::botcolliding(*this, p2, movement))
			pSprite->move(0, movement);
	}
	if (sf::Keyboard::isKeyPressed(right)
		&& !Collision::collisionRightBorder(*this, sf::Vector2<float>(1280, 720 - (175 * 32) / 100)))
	{
		if (!Collision::rightcolliding(*this, p2, movement))
			pSprite->move(movement, 0);
	}
	if (sf::Keyboard::isKeyPressed(left)
		&& !Collision::collisionLeftBorder(*this, sf::Vector2<float>(1280, 720 - (175 * 32) / 100)))
	{
		if (!Collision::leftcolliding(*this, p2, movement))
			pSprite->move(-movement, 0);
	}
	if (sf::Keyboard::isKeyPressed(powerOn))
	{
		powOn = true;
	}
	if (sf::Keyboard::isKeyPressed(powerOff))
	{
		powOn = false;
		
	}
	
	if (!getPStat())
	{
		if (getpower() < 1000)
		{
			setpower(getpower() + 1000*frametime );
		}
		else
		{
			setpower(1000);
		}
	}
}

void Player::handle()
{
}

void Player::Render(sf::RenderWindow * rw)
{
	if (getalive())
	{
		rw->draw(*pSprite);
	}
}

void Player::position(int x, int y)
{
}
