#pragma once
#include "Player.hpp"
#include <SFML\Graphics.hpp>
class Collision
{
public:
	static bool collisionUpBorder	( Player& p, sf::Vector2<float>& size);
	static bool collisionLowBorder	( Player& p, sf::Vector2<float>& size);
	static bool collisionLeftBorder	( Player& p, sf::Vector2<float>& size);
	static bool collisionRightBorder( Player& p, sf::Vector2<float>& size);


	static bool colliding(Player& p1, Player& p2, float& speed);
	
	static bool topcolliding(Player& p1, Player& p2, float& speed);
	static bool botcolliding(Player& p1, Player& p2, float& speed);
	static bool leftcolliding(Player& p1, Player& p2, float& speed);
	static bool rightcolliding(Player& p1, Player& p2, float& speed);


};

