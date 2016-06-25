#include "Game.hpp"




void Game::initGame(int width, int height) {

	CallBack cb = [&] (Scenes& scene){this->setScene(scene);};
	CallBackView cbv = [&](const sf::View& view) {setView(view);};
	startScene = new Splashscreen(width, height, cb,cbv);
	Application::setScene(*startScene);


}

Game::Game(const std::string& title, int width, int height) : Application(title, width, height)
{
	initGame(width, height);

}





Game::~Game()
{
}


