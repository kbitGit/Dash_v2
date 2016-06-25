#pragma once
#include"testHeader.hpp"
#include<Application.hpp>
#include"Tile.h"
#include<iostream>
#include<random>
#include<functional>

#define AliveTilePercent 45

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 100);
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
		text->setText("Recreate");

		addToRender(*text);
		countTilesX = windowSize.x / SpriteSize;
		countTilesY = windowSize.y / SpriteSize;


		Generate();
		generating = false;
	}
	~GameOfLifeScene()
	{
		delete timePassed;
		timePassed = nullptr;
		delete text;
		text = nullptr;
	}
	void Generate() {
		cleanRender();
		addToRender(*text);
		t = IntGrid(countTilesX, IntVec(countTilesY));
		for (int x = 0;x < countTilesX;x++)
		{
			for (int y = 0; y < countTilesY; y++)
			{
				t[x][y] = new Tile(sf::Vector2f(x * SpriteSize, y * SpriteSize), false);
				if (x == 0 || y == 0 || x == countTilesX - 1 || y == countTilesY - 1)
				{
					t[x][y]->setIsWall(true);
					
				}
				else {
					int dice_roll = distribution(generator);
					t[x][y]->setIsWall(dice_roll < AliveTilePercent ? true : false);
				}
			}
		}
		for (int i = 0;i < 5;i++) {
			Smooth();
		}

		for (int x = 0;x < countTilesX;x++)
		{
			for (int y = 0; y < countTilesY; y++)
			{
				addToRender(*t[x][y]);
			}
		}
	}
	void Smooth() {
		for (int x = 0;x < countTilesX;x++)
		{
			for (int y = 0; y < countTilesY; y++)
			{
				if (x == 0 || y == 0 || x == countTilesX - 1 || y == countTilesY - 1)
				{
					continue;
				}
				int count = stillAlive(x, y);
				if (count > 4)
					t[x][y]->setIsWall(true);
				if (count < 4)
					t[x][y]->setIsWall(false);
			}
		}
	}
	void Update(float& frameTime)
	{
		if (text->getsfText().getGlobalBounds().contains(
			call().x,
			call().y
			)
			&& !generating)
		{
			text->setColor(sf::Color::Green);
		}
		else
		{
			text->setColor(sf::Color::White);
		}
		if (text->getsfText().getGlobalBounds().contains(
			call().x,
			call().y
			)
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
			&& !generating
			)
		{
			generating = true;
			Generate();
			generating = false;
		}
	}
	int stillAlive(int x, int y) {
		int count = 0;
		if (x == 0 && y == 0)
		{
			if (t[x + 1][y + 1]->getIsWall())
				count++;
			if (t[x + 1][y]->getIsWall())
				count++;
			if (t[x][y + 1]->getIsWall())
				count++;
			return count;

		}
		if (x == countTilesX - 1 && y == 0)
		{
			if (t[x - 1][y + 1]->getIsWall())
				count++;
			if (t[x - 1][y]->getIsWall())
				count++;
			if (t[x][y + 1]->getIsWall())
				count++;
			return count;

		}
		if (x == countTilesX - 1 && y == countTilesY - 1)
		{
			if (t[x - 1][y - 1]->getIsWall())
				count++;
			if (t[x - 1][y]->getIsWall())
				count++;
			if (t[x][y - 1]->getIsWall())
				count++;
			return count;

		}
		if (x == 0 && y == countTilesY - 1)
		{
			if (t[x + 1][y - 1]->getIsWall())
				count++;
			if (t[x + 1][y]->getIsWall())
				count++;
			if (t[x][y - 1]->getIsWall())
				count++;
			return count;

		}
		if (x == 0) {
			if (t[x][y + 1]->getIsWall())
				count++;
			if (t[x + 1][y + 1]->getIsWall())
				count++;
			if (t[x + 1][y]->getIsWall())
				count++;
			if (t[x + 1][y - 1]->getIsWall())
				count++;
			if (t[x][y - 1]->getIsWall())
				count++;
			return count;

		}
		if (y == 0) {
			if (t[x - 1][y]->getIsWall())
				count++;
			if (t[x - 1][y + 1]->getIsWall())
				count++;
			if (t[x][y + 1]->getIsWall())
				count++;
			if (t[x + 1][y + 1]->getIsWall())
				count++;
			if (t[x + 1][y]->getIsWall())
				count++;
			return count;

		}
		if (x == countTilesX - 1) {
			if (t[x - 1][y - 1]->getIsWall())
				count++;
			if (t[x - 1][y]->getIsWall())
				count++;
			if (t[x - 1][y + 1]->getIsWall())
				count++;
			if (t[x][y + 1]->getIsWall())
				count++;
			if (t[x][y - 1]->getIsWall())
				count++;
			return count;

		}
		if (y == countTilesY - 1) {
			if (t[x - 1][y - 1]->getIsWall())
				count++;
			if (t[x - 1][y]->getIsWall())
				count++;
			if (t[x + 1][y]->getIsWall())
				count++;
			if (t[x + 1][y - 1]->getIsWall())
				count++;
			if (t[x][y - 1]->getIsWall())
				count++;
			return count;

		}
		if (t[x - 1][y - 1]->getIsWall())
			count++;
		if (t[x - 1][y]->getIsWall())
			count++;
		if (t[x - 1][y + 1]->getIsWall())
			count++;
		if (t[x][y + 1]->getIsWall())
			count++;
		if (t[x + 1][y + 1]->getIsWall())
			count++;
		if (t[x + 1][y]->getIsWall())
			count++;
		if (t[x + 1][y - 1]->getIsWall())
			count++;
		if (t[x][y - 1]->getIsWall())
			count++;
		return count;
	}
	void Handle(sf::Event *mainEvent)
	{

	}
private:
	int countTilesX;
	int countTilesY;
	bool upDate;
	bool generating;
	sf::Clock* timePassed;
	uiText* text;
	sf::Font* font;
	IntGrid t;
	CallBack call;
};