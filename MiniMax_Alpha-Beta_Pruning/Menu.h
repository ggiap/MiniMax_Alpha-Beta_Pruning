#pragma once
#include <SFML\Graphics.hpp>

const auto menu_items = 4;

class Menu : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	int selectedindex;
	sf::Font font;
	sf::Text menu[menu_items];
	sf::Texture background;
	sf::Sprite  sprite_background;

public:
	Menu(size_t width, size_t height);

	void MoveUp();
	void MoveDown();
	int  Get_Pressed_Index();
};
