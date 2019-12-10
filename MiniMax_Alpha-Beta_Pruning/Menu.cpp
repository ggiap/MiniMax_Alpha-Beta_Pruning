#include "Menu.h"

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_background);
	for (const auto &button : mainMenu)
	{
		target.draw(button);
	}
}

void Menu::HandleEvents()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (mmButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					abButton.ResetButtonState();
					mmButton.isPressed = true;

					mmButton.getButtonText().setFillColor(ORANGE);
					abButton.getButtonText().setFillColor(sf::Color::White);
				}
				else if (abButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					abButton.isPressed = true;
					mmButton.ResetButtonState();

					abButton.getButtonText().setFillColor(ORANGE);
					mmButton.getButtonText().setFillColor(sf::Color::White);
				}

				if (diffEasyButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					diffEasyButton.isPressed = true;
					diffIntermButton.ResetButtonState();
					diffHardButton.ResetButtonState();

					diffEasyButton.setButtonTextColor(ORANGE);
					diffIntermButton.setButtonTextColor(sf::Color::White);
					diffHardButton.setButtonTextColor(sf::Color::White);
				}
				else if (diffIntermButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					diffIntermButton.isPressed = true;
					diffEasyButton.ResetButtonState();
					diffHardButton.ResetButtonState();

					diffEasyButton.setButtonTextColor(sf::Color::White);
					diffIntermButton.setButtonTextColor(ORANGE);
					diffHardButton.setButtonTextColor(sf::Color::White);
				}
				else if (diffHardButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					diffHardButton.isPressed = true;
					diffEasyButton.ResetButtonState();
					diffIntermButton.ResetButtonState();

					diffEasyButton.setButtonTextColor(sf::Color::White);
					diffIntermButton.setButtonTextColor(sf::Color::White);
					diffHardButton.setButtonTextColor(ORANGE);
				}

				if (playerButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					playerButton.isPressed = true;
					opponentButton.ResetButtonState();

					playerButton.setButtonTextColor(ORANGE);
					opponentButton.setButtonTextColor(sf::Color::White);
				}
				else if (opponentButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					opponentButton.isPressed = true;
					playerButton.ResetButtonState();

					playerButton.setButtonTextColor(sf::Color::White);
					opponentButton.setButtonTextColor(ORANGE);
				}

				if (backButton.getRect().getGlobalBounds().contains(mousePosF))
					backButton.isPressed = true;
			}
		}

		if (event.type == sf::Event::MouseMoved)
		{
			if (backButton.getRect().getGlobalBounds().contains(mousePosF))
				backButton.setButtonTextColor(backButton.getHoverColor());
			else
				backButton.setButtonTextColor(sf::Color::White);
		}

		if (event.type == sf::Event::Closed)
			window->close();
	}
}

Menu::Menu(sf::RenderWindow &win, size_t width, size_t height)
{
	window = &win;

	if (!font.loadFromFile("Font\\OCRAEXT.ttf"))
	{
		exit(EXIT_FAILURE);
	}

	mainMenu.at(0).buttonConfig(sf::Vector2f(180, 30),
								sf::Vector2f(width / 2.95, height / (menu_items + 1) * 2),
								sf::Color(50, 100, 200, 95),
								sf::Color::White,
								"Singleplayer");
	mainMenu.at(0).setHoverColor(ORANGE);

	mainMenu.at(1).buttonConfig(sf::Vector2f(165, 30),
								sf::Vector2f(width / 2.85, height / (menu_items + 1) * 2.7),
								sf::Color(50, 100, 200, 95),
								sf::Color::White,
								"Multiplayer");
	mainMenu.at(1).setHoverColor(ORANGE);

	mainMenu.at(2).buttonConfig(sf::Vector2f(110, 30),
								sf::Vector2f(width / 2.55, height / (menu_items + 1) * 3.4),
								sf::Color(50, 100, 200, 95),
								sf::Color::White,
								"Options");
	mainMenu.at(2).setHoverColor(ORANGE);

	mainMenu.at(3).buttonConfig(sf::Vector2f(65, 30),
								sf::Vector2f(width / 2.3, height / (menu_items + 1) * 4.1),
								sf::Color(50, 100, 200, 95),
								sf::Color::White,
								"Exit");
	mainMenu.at(3).setHoverColor(ORANGE);

	if (!background.loadFromFile("Images\\background1.jpg"))
	{
		exit(EXIT_FAILURE);
	}

	sprite_background.setTexture(background);
	sprite_background.setScale(1, 1);
	sprite_background.setPosition(sf::Vector2f(width / 640, height / 400));

	mmButton.buttonConfig(  sf::Vector2f(110, 30), sf::Vector2f(120, 80), sf::Color(50,100,200,95), sf::Color::White, "MiniMax");
	abButton.buttonConfig(  sf::Vector2f(150, 30), sf::Vector2f(350, 80), sf::Color(50,100,200,95), ORANGE, "Alpha-Beta");
	
	diffEasyButton.buttonConfig(sf::Vector2f(65, 30), sf::Vector2f(50, 250), sf::Color(50, 100, 200, 95), ORANGE, "Easy");
	diffIntermButton.buttonConfig(sf::Vector2f(180, 30), sf::Vector2f(200, 250), sf::Color(50, 100, 200, 95), sf::Color::White, "Intermidiate");
	diffHardButton.buttonConfig(sf::Vector2f(65, 30), sf::Vector2f(450, 250), sf::Color(50, 100, 200, 95), sf::Color::White, "Hard");

	playerButton.buttonConfig(sf::Vector2f(90, 30), sf::Vector2f(130, 460), sf::Color(50, 100, 200, 95), ORANGE, "Player");
	opponentButton.buttonConfig(sf::Vector2f(120, 30), sf::Vector2f(350, 460), sf::Color(50, 100, 200, 95), sf::Color::White, "Opponent");

	backButton.buttonConfig(sf::Vector2f(65, 30), sf::Vector2f(520, 560), sf::Color(50, 100, 200, 95), sf::Color::White, "Back");
	backButton.setHoverColor(ORANGE);

	if (!option_background.loadFromFile("Images\\background.jpg"))
	{
		exit(EXIT_FAILURE);
	}

	sprite_option_background.setTexture(option_background);
	sprite_option_background.setScale(1, 1);
	sprite_option_background.setPosition(sf::Vector2f(width / 640, height / 400));

	optionText.setString("  Choose AI algorithm");
	optionText.setFont(font);
	optionText.setFillColor(sf::Color::White);
	optionText.setPosition(100,10);

	optionText2.setString("  Choose computer difficulty\n	(one-player game only)");
	optionText2.setFont(font);
	optionText2.setFillColor(sf::Color::White);
	optionText2.setPosition(30, 170);

	optionText3.setString("		Who plays first\n	(one-player game only)");
	optionText3.setFont(font);
	optionText3.setFillColor(sf::Color::White);
	optionText3.setPosition(30, 350);

	algChoice = false;
	playerTurn = true;
	difficulty = 0;
}

void Menu::Options()
{
	while (!backButton.isPressed)
	{
		HandleEvents();

		if (mmButton.isPressed)
			algChoice = true;
		else if (abButton.isPressed)
			algChoice = false;

		if (diffEasyButton.isPressed)
			difficulty = 0;
		else if (diffIntermButton.isPressed)
			difficulty = 2;
		else if (diffHardButton.isPressed)
			difficulty = 10;

		if (playerButton.isPressed)
			playerTurn = true;
		else if (opponentButton.isPressed)
			playerTurn = false;

		window->clear();
		window->draw(sprite_option_background);
		window->draw(optionText);
		window->draw(optionText2);
		window->draw(optionText3);
		window->draw(mmButton);
		window->draw(abButton);
		window->draw(diffEasyButton);
		window->draw(diffIntermButton);
		window->draw(diffHardButton);
		window->draw(playerButton);
		window->draw(opponentButton);
		window->draw(backButton);
		window->display();
	}

	backButton.ResetButtonState();
}

bool Menu::getAlgorithmChoice()
{
	return algChoice;
}

bool Menu::WhoPlaysFirst()
{
	return playerTurn;
}

int Menu::getDifficultyChoice()
{
	return difficulty;
}

int Menu::getPressedButton()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	for (int i = 0; i < mainMenu.size(); ++i)
	{
		if (mainMenu.at(i).getRect().getGlobalBounds().contains(mousePosF))
		{
			return i;
		}
	}

	return -1;
}

void Menu::ActivateBtnHoverEffect()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	for (auto& button : mainMenu)
	{
		if (button.getRect().getGlobalBounds().contains(mousePosF))
			button.setButtonTextColor(button.getHoverColor());
		else
			button.setButtonTextColor(sf::Color::White);
	}
}
