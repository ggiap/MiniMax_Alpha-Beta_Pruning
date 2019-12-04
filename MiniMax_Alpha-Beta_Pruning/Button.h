#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

const sf::Color ORANGE = sf::Color(250, 100, 0, 250);

class Button : public sf::Drawable
{
public:
	Button();
	Button(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Color& fillColor = sf::Color::Green);

	sf::RectangleShape& getRect();
	const sf::RectangleShape& getRect() const;
	sf::Text& getButtonText();
	sf::Color getHoverColor();
	void buttonConfig
	(
		const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Color& fillColor,
		const sf::Color& textfillColor,
		const string& name
	);
	void setPosition(const sf::Vector2f&);
	void setHoverColor(const sf::Color&);
	void setButtonTextColor(const sf::Color&);
	void ResetButtonState();

	bool isPressed;

private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
	sf::RectangleShape rect;
	sf::Text buttonText;
	sf::Font font;
	sf::Color hoverColor;
};