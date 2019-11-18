#pragma once
#include <SFML\Graphics.hpp>

constexpr auto menu_items = 4;

class Menu
{

	private:

		int selectedindex;
		sf::Font font;
		sf::Text menu[menu_items];
		sf::Texture background;
		sf::Sprite  sprite_background;

	public:

		Menu(float width, float height);
		~Menu();

		void DrawMenu(sf::RenderWindow &window);
		void DrawBackground(sf::RenderWindow &window);
		void MoveUp();
		void MoveDown();
		int  Get_Pressed_Index();
};
