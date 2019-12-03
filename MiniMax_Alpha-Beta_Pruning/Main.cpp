#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "Menu.h"
#include "Tic_Tac_Toe.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "MiniMax_Alpha-Beta Pruning");

	Menu menu(window, window.getSize().x, window.getSize().y);
	Tic_Tac_Toe game(window);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseMoved)
			{
				menu.ActivateBtnHoverEffect();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int result = menu.getPressedButton();

					if (result == 0) // One-player game
					{
						game.StartGame(true, menu.WhoPlaysFirst(), menu.getAlgorithmChoice(), menu.getDifficultyChoice());
						game.ResetBoard();
					}
					else if (result == 1) // Two-player game
					{
						game.StartGame(false, menu.WhoPlaysFirst(), menu.getAlgorithmChoice(), menu.getDifficultyChoice());
						game.ResetBoard();
					}
					else if (result == 2) // Options
					{
						menu.Options();
					}
					else if (result == 3) // Exit
					{
						window.close();
					}
					else
						cout << "No buttons are being pressed!\n";
				}
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.draw(menu);
		window.display();
	}

	return 0;
}