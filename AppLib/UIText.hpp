#pragma once
#include "Renderable.hpp"
class uiText : public Renderable {
public:
	uiText(sf::Font* uiFont, sf::Vector2f position) {
		uiTextToShow = new sf::Text();
		uiTextToShow->setFont(*uiFont);
		uiTextToShow->setPosition(position);

		uiTextToShow->setString("Test");

	}
	void setText(std::string toChange) {
		uiTextToShow->setString(toChange);
	}
	void setColor(sf::Color c) {
		uiTextToShow->setColor(c);
	}
	sf::Text getsfText() {
		return *uiTextToShow;
	}
	sf::Color getColor() {
		return uiTextToShow->getColor();
	}
	void Render(sf::RenderWindow *rw) {
		rw->draw(*uiTextToShow);

	}

	~uiText() {
		delete uiTextToShow;
		uiTextToShow = nullptr;
	}
private:
	sf::Text* uiTextToShow;
};