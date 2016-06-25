#pragma once
#include"testHeader.hpp"
#include <Renderable.hpp>
#include<iostream>
class Tile : public Renderable {
public:
	Tile(const sf::Vector2f& pos, bool Wall)
	{
		
		black = new sf::Image();
		black->create(SpriteSize, SpriteSize, sf::Color::Black);

		white = new sf::Image();
		white->create(SpriteSize, SpriteSize, sf::Color::White);

		isWall = Wall;
		tileTexture = std::move(std::unique_ptr<sf::Texture>(new sf::Texture()));
		tileSprite = std::move(std::unique_ptr<sf::Sprite>(new sf::Sprite()));
		tileTexture->loadFromImage(*white);
		tileSprite->setTexture(*tileTexture);
		tileSprite->setPosition(pos);
	}

	~Tile()
	{
		delete black;
		delete white;
		black = nullptr;
		white = nullptr;
	}
	void Render(sf::RenderWindow *rw) {
		if (isWall)
		{
			tileTexture->loadFromImage(*black);
			tileSprite->setTexture(*tileTexture);
			rw->draw(*tileSprite);
		}
		else
		{
			tileTexture->loadFromImage(*white);
			tileSprite->setTexture(*tileTexture);
			rw->draw(*tileSprite);

		}

	
	}


	bool getIsWall() { return isWall; };
	void setIsWall(bool set) { isWall = set; };

	sf::Vector2f getTilePos() { return tileSprite->getPosition(); };

private:
	std::unique_ptr<sf::Sprite> tileSprite;
	std::unique_ptr<sf::Texture> tileTexture;
	sf::Image* black;
	sf::Image* white;

	bool isWall;

};