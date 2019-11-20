#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "Menu.h"
#include "Tic_Tac_Toe.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "MiniMax_Alpha-Beta Pruning");

	Menu menu(window.getSize().x,window.getSize().y);
	Tic_Tac_Toe game(window);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case::sf::Keyboard::Return:
					switch (menu.Get_Pressed_Index())
					{
					case 0:
						//std::cout << "One Player" << std::endl;
						
						break;

					case 1:
						//std::cout << "Two Player" << std::endl;
						game.StartGame();
						game.ResetBoard();
						break;

					case 2:
						//std::cout << "Options" << std::endl;
						
						break;

					case 3:
						//std::cout << "Exit" << std::endl;
						window.close();
						break;
					}
				}
				break;
			}
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear(sf::Color::White);
		window.draw(menu);
		window.display();
	}

	return 0;
}