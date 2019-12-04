#pragma once
#include <SFML\Graphics.hpp>

#include "Button.h"

const auto menu_items = 4;

class Menu : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	void HandleEvents();

	sf::RenderWindow* window;
	sf::Font font;
	sf::Text optionText;
	sf::Text optionText2;
	sf::Text optionText3;
	sf::Texture background;
	sf::Sprite  sprite_background;
	sf::Texture option_background;
	sf::Sprite  sprite_option_background;
	std::vector<Button> mainMenu{ 4, Button() };
	Button mmButton;
	Button abButton;
	Button diffEasyButton;
	Button diffIntermButton;
	Button diffHardButton;
	Button playerButton;
	Button opponentButton;
	Button backButton;
	bool algChoice;
	bool playerTurn;
	int difficulty;

public:
	Menu(sf::RenderWindow&, size_t, size_t);

	void Options();
	bool getAlgorithmChoice();
	bool WhoPlaysFirst();
	int getDifficultyChoice();
	int getPressedButton();
	void ActivateBtnHoverEffect();
};