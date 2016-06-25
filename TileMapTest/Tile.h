#pragma once
#include <Renderable.hpp>
#include<iostream>
class Tile : public Renderable {
public:
	Tile(const sf::Vector2f& pos, bool alive)
	{
		
		black = new sf::Image();
		black->create(32, 32, sf::Color::Black);

		white = new sf::Image();
		white->create(32, 32, sf::Color::White);

		isAlive = alive;
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
		std::cout << "Destroyed" << std::endl;
		black = nullptr;
		white = nullptr;
	}
	void Render(sf::RenderWindow *rw) {
		if (isAlive)
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

		if (tileSprite->getGlobalBounds().contains(
			sf::Mouse::getPosition(*rw).x,
			sf::Mouse::getPosition(*rw).y)
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
			)
		{
			isAlive = !isAlive;
		}
	
	}


	bool getIsAlive() { return isAlive; };
	void setAlive(bool set) { isAlive = set; };

	sf::Vector2f getTilePos() { return tileSprite->getPosition(); };

private:
	std::unique_ptr<sf::Sprite> tileSprite;
	std::unique_ptr<sf::Texture> tileTexture;
	sf::Image* black;
	sf::Image* white;

	bool isAlive;

};