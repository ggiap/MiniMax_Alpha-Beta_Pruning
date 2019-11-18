#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("OCRAEXT.ttf"))
	{
		EXIT_FAILURE;
	}
	//Error while load the font
	
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


	if (!background.loadFromFile("background1.jpg"))
	{
		EXIT_FAILURE;
	}
	//Error while load the background

	sprite_background.setTexture(background);
	sprite_background.setScale(1, 1);
	sprite_background.setPosition(sf::Vector2f(width / 640, height / 400));

	
}
//Constructor

Menu::~Menu() {}
//Destructor

void Menu::DrawMenu(sf::RenderWindow &window)
{
	for (int i = 0; i < menu_items; ++i)
	{
		window.draw(menu[i]);
	}
}
//Draw the menu

void Menu::DrawBackground(sf::RenderWindow &window)
{
	window.draw(sprite_background);
}
//Draw the background

void Menu::MoveUp()
{
	if(selectedindex - 1 >= 0)
	{
		menu[selectedindex].setFillColor(sf::Color::White);
		--selectedindex;
		menu[selectedindex].setFillColor(sf::Color::Red);
	}
}
//Move up

void Menu::MoveDown()
{
	if (selectedindex + 1 < menu_items)
	{
		menu[selectedindex].setFillColor(sf::Color::White);
		++selectedindex;
		menu[selectedindex].setFillColor(sf::Color::Red);
	}
}
//Move Down

int Menu::Get_Pressed_Index()
{
	return selectedindex;
}
//Return the index which pressed