#pragma once
#include<Application.hpp>
#include"Tile.h"
#include<iostream>
#include<functional>

#define AliveTilePercent 20
typedef std::function<sf::Vector2i()> CallBack;

class GameOfLifeScene :public Scenes
{
	typedef std::vector<Tile*> IntVec;
	typedef std::vector<IntVec> IntGrid;

public:
	GameOfLifeScene(const sf::Vector2f& windowSize, CallBack cb)
	{
		call = cb;
		upDate = true;
		timePassed = new sf::Clock();
		font = new sf::Font();
		text = new uiText(font, sf::Vector2f(1300, 200));

		font->loadFromFile("Simpleman.ttf");
		text->setText("Pause");

		addToRender(*text);
		countTilesX = windowSize.x / 32;
		countTilesY = windowSize.y / 32;
		t = IntGrid(countTilesX, IntVec(countTilesY));

		for (int x = 0;x < countTilesX;x++)
		{
			for (int y = 0; y < countTilesY; y++)
			{
				t[x][y] = new Tile(sf::Vector2f(x * 32, y * 32), false);
				addToRender(*t[x][y]);
			}
		}

	}
	~GameOfLifeScene()
	{
		delete timePassed;
		timePassed = nullptr;
		delete text;
		text = nullptr;
	}
	void Update(float& frameTime)
	{
		if (text->getsfText().getGlobalBounds().contains(
			call().x,
			call().y
			)
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
			)
		{
			upDate = !upDate;
			if (text->getColor() == sf::Color::Green)
			{
				text->setColor(sf::Color::White);
			}
			else
			{
				text->setColor(sf::Color::Green);
			}
		}
		if (timePassed->getElapsedTime().asSeconds() >= 1 && upDate)
		{
			for (int x = 0;x < countTilesX;x++)
			{
				for (int y = 0; y < countTilesY; y++)
				{
					bool s = stillAlive(x, y,t[x][y]->getIsAlive());
					t[x][y]->setAlive(s);
				}
			}
			timePassed->restart();
		}
	}
	bool stillAlive(int x, int y,bool current) {
		int count = 0;
		if (x == 0 && y == 0)
		{
			if (t[x + 1][y + 1]->getIsAlive())
				count++;
			if (t[x + 1][y]->getIsAlive())
				count++;
			if (t[x][y + 1]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (x == countTilesX - 1 && y == 0)
		{
			if (t[x - 1][y + 1]->getIsAlive())
				count++;
			if (t[x - 1][y]->getIsAlive())
				count++;
			if (t[x][y + 1]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (x == countTilesX - 1 && y == countTilesY - 1)
		{
			if (t[x - 1][y - 1]->getIsAlive())
				count++;
			if (t[x - 1][y]->getIsAlive())
				count++;
			if (t[x][y - 1]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (x == 0 && y == countTilesY - 1)
		{
			if (t[x + 1][y - 1]->getIsAlive())
				count++;
			if (t[x + 1][y]->getIsAlive())
				count++;
			if (t[x][y - 1]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (x == 0) {
			if (t[x][y + 1]->getIsAlive())
				count++;
			if (t[x + 1][y + 1]->getIsAlive())
				count++;
			if (t[x + 1][y]->getIsAlive())
				count++;
			if (t[x + 1][y - 1]->getIsAlive())
				count++;
			if (t[x][y - 1]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (y == 0) {
			if (t[x - 1][y]->getIsAlive())
				count++;
			if (t[x - 1][y + 1]->getIsAlive())
				count++;
			if (t[x][y + 1]->getIsAlive())
				count++;
			if (t[x + 1][y + 1]->getIsAlive())
				count++;
			if (t[x + 1][y]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (x == countTilesX - 1) {
			if (t[x - 1][y - 1]->getIsAlive())
				count++;
			if (t[x - 1][y]->getIsAlive())
				count++;
			if (t[x - 1][y + 1]->getIsAlive())
				count++;
			if (t[x][y + 1]->getIsAlive())
				count++;
			if (t[x][y - 1]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (y == countTilesY - 1) {
			if (t[x - 1][y - 1]->getIsAlive())
				count++;
			if (t[x - 1][y]->getIsAlive())
				count++;
			if (t[x + 1][y]->getIsAlive())
				count++;
			if (t[x + 1][y - 1]->getIsAlive())
				count++;
			if (t[x][y - 1]->getIsAlive())
				count++;
			if (count == 3)
				return true;
			if (count == 2)
				return current;
			return false;
		}
		if (t[x - 1][y - 1]->getIsAlive())
			count++;
		if (t[x - 1][y]->getIsAlive())
			count++;
		if (t[x - 1][y + 1]->getIsAlive())
			count++;
		if (t[x][y + 1]->getIsAlive())
			count++;
		if (t[x + 1][y + 1]->getIsAlive())
			count++;
		if (t[x + 1][y]->getIsAlive())
			count++;
		if (t[x + 1][y - 1]->getIsAlive())
			count++;
		if (t[x][y - 1]->getIsAlive())
			count++;
		if (count == 3 )
			return true;
		if (count == 2)
			return current;
		return false;
	}
	void Handle(sf::Event *mainEvent)
	{

	}
private:
	int countTilesX;
	int countTilesY;
	bool upDate;
	sf::Clock* timePassed;
	uiText* text;
	sf::Font* font;
	IntGrid t;
	CallBack call;
};