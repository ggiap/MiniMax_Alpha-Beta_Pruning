#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Menu.h"
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 470), "MiniMax_Alpha-Beta Pruning");

	Menu menu(window.getSize().x,window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{

			switch (event.type)
			{
				case sf::Event::KeyReleased:

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
									std::cout << "One Player" << std::endl;
									//Do code here
									break;
								case 1:
									std::cout << "Two Player" << std::endl;
									//DO code here
									break;
								case 2:
									std::cout << "Options"    << std::endl;
									//Do code here
									break;
								case 3:
									std::cout << "Exit"       << std::endl;
									window.close();
									break;								
							}						
					}
				break;
				case sf::Event::Closed:
					window.close();
					break;
			}		
		}

		window.clear();
		menu.DrawBackground(window);
		menu.DrawMenu(window);
		window.display();
	}

	return 0;
}