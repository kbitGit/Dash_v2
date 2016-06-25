#pragma once

#include <SFML/Graphics.hpp>
#include<memory>
#include "Scenes.hpp"
#include "Renderable.hpp"
#include "UIText.hpp"

class Application
{
public:
	Application(const std::string& title, int width, int height);
	void Run();
	void setScene(Scenes& toChange);
	void setView(const sf::View& view);
	sf::Vector2i mousePositionInWindow() 
	{
		return sf::Mouse::getPosition(*window);
	}
	virtual ~Application();

protected:
	float frameTime;
private:
	bool running = false;
	sf::Event *mainEvent;
	sf::RenderWindow *window;
	sf::Clock *clock;
	std::unique_ptr<Scenes> actualScene;
	

};

