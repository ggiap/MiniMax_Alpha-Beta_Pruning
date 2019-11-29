#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Button.h"

const auto menu_items = 4;

class Menu : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
	void HandleEvents(sf::RenderWindow &);

	int selectedindex;
	sf::Font font;
	sf::Text menu[menu_items];
	sf::Texture background;
	sf::Sprite  sprite_background;
	Button mmButton;
	Button abButton;
	Button backButton;

public:
	Menu(size_t width, size_t height);

	void MoveUp();
	void MoveDown();
	int  Get_Pressed_Index();
	void chooseAlgo(sf::RenderWindow &);

	bool algChoice;
};
