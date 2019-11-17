#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 400), "MiniMax_Alpha-Beta Pruning");

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(150, 150, 150));
		//window.draw();
		window.display();
	}

	return 0;
}