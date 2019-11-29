#include "Menu.h"

void Menu::draw(sf::RenderTarget&target, sf::RenderStates states) const
{
	target.draw(sprite_background);
	for (int i = 0; i < menu_items; ++i)
	{
		target.draw(menu[i]);
	}	
}

void Menu::HandleEvents(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				if (mmButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					abButton.isPressed = false;
					mmButton.isPressed = true;

					mmButton.getRect().setFillColor(sf::Color::Blue);
					abButton.getRect().setFillColor(sf::Color::Cyan);
				}
				if (abButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					abButton.isPressed = true;
					mmButton.isPressed = false;

					abButton.getRect().setFillColor(sf::Color::Blue);
					mmButton.getRect().setFillColor(sf::Color::Cyan);
				}
				if (backButton.getRect().getGlobalBounds().contains(mousePosF))
					backButton.isPressed = true;				
			}
		}

		if (event.type == sf::Event::Closed)
			window.close();
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

	mmButton.buttonConfig(sf::Vector2f(150, 50), sf::Vector2f(200, 200), sf::Color::Cyan, "MiniMax");
	abButton.buttonConfig(sf::Vector2f(150, 50), sf::Vector2f(400, 200), sf::Color::Blue, "Alpha-Beta");
	backButton.buttonConfig(sf::Vector2f(150, 50), sf::Vector2f(450, 550), sf::Color::Cyan, "Back");
	
	algChoice = false;
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

void Menu::chooseAlgo(sf::RenderWindow &window)
{
	while (!backButton.isPressed)
	{
		HandleEvents(window);

		if (mmButton.isPressed)
			algChoice = true;
		else if (abButton.isPressed)
			algChoice = false;

		window.clear(sf::Color::White);
		mmButton.draw(window);
		abButton.draw(window);
		backButton.draw(window);
		window.display();
	}

	backButton.isPressed = false;
}
