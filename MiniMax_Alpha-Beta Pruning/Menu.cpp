#include "Menu.h"

void Menu::draw(sf::RenderTarget&target, sf::RenderStates states) const
{
	target.draw(sprite_background);
	for (int i = 0; i < menu_items; ++i)
	{
		target.draw(menu[i]);
	}	
}

Menu::Menu(size_t width, size_t height)
{
	if (!font.loadFromFile("Font\\OCRAEXT.ttf"))
	{
		exit(EXIT_FAILURE);
	}
	
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("One Player");
	menu[0].setPosition(sf::Vector2f(width / 2.8, height / (menu_items + 1) * 2));			

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Two Player");
	menu[1].setPosition(sf::Vector2f(width / 2.8, height / (menu_items + 1) * 2.7));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Options");
	menu[2].setPosition(sf::Vector2f(width / 2.47, height / (menu_items + 1) * 3.4));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2.25, height / (menu_items + 1) * 4.1));

	selectedindex = 0;

	if (!background.loadFromFile("Images\\background1.jpg"))
	{
		exit(EXIT_FAILURE);
	}

	sprite_background.setTexture(background);
	sprite_background.setScale(1, 1);
	sprite_background.setPosition(sf::Vector2f(width / 640, height / 400));	
}

void Menu::MoveUp()
{
	if(selectedindex - 1 >= 0)
	{
		menu[selectedindex].setFillColor(sf::Color::White);
		--selectedindex;
		menu[selectedindex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedindex + 1 < menu_items)
	{
		menu[selectedindex].setFillColor(sf::Color::White);
		++selectedindex;
		menu[selectedindex].setFillColor(sf::Color::Red);
	}
}

int Menu::Get_Pressed_Index()
{
	return selectedindex;
}