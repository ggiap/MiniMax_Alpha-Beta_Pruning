#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Button
{
public:
	Button();
	Button(
		const sf::Vector2f &size,
		const sf::Vector2f &position,
		const sf::Color &fillColor = sf::Color::Green);

	sf::RectangleShape& getRect();
	const sf::RectangleShape& getRect() const;
	sf::Text& getButtonText();
	void buttonConfig
	(
		const sf::Vector2f &size,
		const sf::Vector2f &position,
		const sf::Color &fillColor,
		const string &name
	);
	void setPosition(const sf::Vector2f &position);
	void setHoverColor(const sf::Color &color);
	void draw(sf::RenderWindow &window);
	bool buttonConfigured; //Used for backButton only.
	bool isPressed;
private:
	sf::RectangleShape rect;
	sf::Text buttonText;
	sf::Font font;
	sf::Color hoverColor;
};

