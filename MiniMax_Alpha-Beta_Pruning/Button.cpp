#include "Button.h"

Button::Button()
{
	isPressed = false;
}

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& fillColor)
	:rect(size)
{
	rect.setPosition(position);
	rect.setFillColor(fillColor);
	isPressed = false;
}

sf::RectangleShape& Button::getRect()
{
	return rect;
}

const sf::RectangleShape& Button::getRect() const
{
	return rect;
}

sf::Text& Button::getButtonText()
{
	return buttonText;
}

sf::Color Button::getHoverColor()
{
	return hoverColor;
}

void Button::buttonConfig(	const sf::Vector2f& size = sf::Vector2f(0.f, 0.f),
							const sf::Vector2f& position = sf::Vector2f(0.f, 0.f),
							const sf::Color& fillColor = sf::Color::White,
							const sf::Color& textfillColor = sf::Color::White,
							const string& name = "Button")
{
	rect.setSize(size);
	rect.setPosition(position);
	rect.setFillColor(fillColor);

	if (!font.loadFromFile("Font/OCRAEXT.ttf"))
		cerr << "Can't load font!" << endl;

	buttonText.setFont(font);
	buttonText.setCharacterSize(25);
	buttonText.setString(name);
	buttonText.setPosition(rect.getPosition().x + 3, rect.getPosition().y - 4);
	buttonText.setFillColor(textfillColor);
}

void Button::setPosition(const sf::Vector2f& position)
{
	rect.setPosition(position);
	buttonText.setPosition(rect.getPosition().x + 3, rect.getPosition().y - 4);
}

void Button::setHoverColor(const sf::Color& color)
{
	hoverColor = color;
}

void Button::setButtonTextColor(const sf::Color& color)
{
	buttonText.setFillColor(color);
}

void Button::ResetButtonState()
{
	isPressed = false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect);
	target.draw(buttonText);
}