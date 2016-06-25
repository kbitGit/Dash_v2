#include "Application.hpp"



Application::Application(const std::string& title, int width, int height)
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	mainEvent = new sf::Event();
	clock = new sf::Clock();
	
	running=true;

}
void Application::Run()
{
	if (actualScene != NULL)
	{
		
		while (running)
		{
			frameTime = clock->getElapsedTime().asSeconds();
			while (window->pollEvent(*mainEvent))
			{

				if (mainEvent->type == sf::Event::Closed)
					running = false;
				actualScene->Handle(mainEvent);
				
			}
			actualScene->Update(frameTime);
			window->clear();
			actualScene->Render(window);
			window->display();
			clock->restart();
		} 
	}

}

void Application::setScene(Scenes & toChange)
{
	actualScene = std::move(std::unique_ptr<Scenes>(&toChange));
}

void Application::setView(const sf::View & view)
{
	window->setView(view);
}

Application::~Application()
{

	delete window;
	delete mainEvent;
	delete clock;

	window = nullptr;
	mainEvent = nullptr;
	clock = nullptr;
}

