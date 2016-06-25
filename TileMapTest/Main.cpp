#include<Application.hpp>
#include"GameOfLifeScene.h"
typedef std::function<sf::Vector2i()> CallBack;

class Game :public Application
{
public:
	Game(const std::string& title, int width, int height) : Application(title, width, height) 
	{
		CallBack cb = [&]() {return this->mousePositionInWindow();};
		setScene(*(new GameOfLifeScene(sf::Vector2f(1280, height), cb)));
	}
	~Game() {
	}
};


int main() {
	Game g("Game of Lime", 1600, 720);
	g.Run();
	return 0;
}