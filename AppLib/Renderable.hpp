#pragma once

#include<SFML\Graphics.hpp>

class Renderable {
public:
	virtual void Render(sf::RenderWindow *rw) = 0;
	virtual ~Renderable() {};
};
