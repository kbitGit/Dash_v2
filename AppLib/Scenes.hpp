#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "Renderable.hpp"
class Scenes {
public:
	 virtual ~Scenes() {
		 cleanRender();
	}
	 void cleanRender() {
		 while (!RenderQueue.empty())
		 {
			 RenderQueue.pop_back();
		 }
	 }
	void Render(sf::RenderWindow *rw) {
		for (auto &toRender : RenderQueue) {
			toRender->Render(rw);
		}
	};
	virtual void Update(float& frameTime) = 0;
	virtual void Handle(sf::Event *mainEvent) = 0;
	void addToRender(Renderable& renderObject) {
		RenderQueue.push_back(&renderObject);
	}
private:
	std::vector<Renderable*> RenderQueue;

};
