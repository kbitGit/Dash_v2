#include "Collision.hpp"


bool Collision::collisionUpBorder(Player & p, sf::Vector2<float>& size)
{
	if (p.getpositiony() > 0)
		return false;
	return true;
}

bool Collision::collisionLowBorder(Player & p, sf::Vector2<float>& size)
{
	if (p.getpositiony() + (32 * 2.5f) < size.y)
		return false;
	return true;
}

bool Collision::collisionLeftBorder(Player & p, sf::Vector2<float>& size)
{
	if (p.getpositionx() > 0)
		return false;
	return true;
}

bool Collision::collisionRightBorder(Player & p, sf::Vector2<float>& size)
{
	if (p.getpositionx() + (32 * 2.5f) < size.x)
		return false;
	return true;
}



bool Collision::colliding(Player & p1, Player & p2, float & speed)
{
	if (p1.getpositionx() < p2.getpositionx() + (33 * 2.5)
		&& p1.getpositionx() + (33 * 2.5) > p2.getpositionx()
		&& p1.getpositiony() < p2.getpositiony() + (33 * 2.5)
		&& p1.getpositiony() + (33 * 2.5) > p2.getpositiony())
		return true;

	return false;
}

bool Collision::topcolliding(Player & p1, Player & p2, float & speed)
{
	if (p1.getpositionx() < p2.getpositionx() + (32 * 2.5)
		&& p1.getpositionx() + (32 * 2.5) > p2.getpositionx()
		&& p1.getpositiony() - speed < p2.getpositiony() + (32 * 2.5)
		&& p1.getpositiony() + (32 * 2.5) - speed > p2.getpositiony())
		return true;

	return false;
}

bool Collision::botcolliding(Player & p1, Player & p2, float & speed)
{
	if (p1.getpositionx() < p2.getpositionx() + (32 * 2.5)
		&& p1.getpositionx() + (32 * 2.5) > p2.getpositionx()
		&& p1.getpositiony() + speed < p2.getpositiony() + (32 * 2.5)
		&& p1.getpositiony() + (32 * 2.5) + speed > p2.getpositiony())
		return true;

	return false;
}

bool Collision::leftcolliding(Player & p1, Player & p2, float & speed)
{
	if (p1.getpositionx() - speed < p2.getpositionx() + (32 * 2.5)
		&& p1.getpositionx() + (32 * 2.5) - speed > p2.getpositionx()
		&& p1.getpositiony() < p2.getpositiony() + (32 * 2.5)
		&& p1.getpositiony() + (32 * 2.5) > p2.getpositiony())
		return true;

	return false;
}

bool Collision::rightcolliding(Player & p1, Player & p2, float & speed)
{
	if (p1.getpositionx() + speed < p2.getpositionx() + (32 * 2.5)
		&& p1.getpositionx() + (32 * 2.5) + speed > p2.getpositionx()
		&& p1.getpositiony() < p2.getpositiony() + (32 * 2.5)
		&& p1.getpositiony() + (32 * 2.5) > p2.getpositiony())
		return true;

	return false;
}

