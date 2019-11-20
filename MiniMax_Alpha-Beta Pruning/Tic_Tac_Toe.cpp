#include "Tic_Tac_Toe.h"


void Tic_Tac_Toe::StartGame()
{
	while (!gameOver)
	{
		HandleEvents();		
		
		window->clear(sf::Color::White);
		draw(*window, sf::RenderStates::Default);
		window->display();

		gameOver = GameCondition();
	}

	while (!anyKeyPressed)
	{
		HandleEvents();

		window->clear(sf::Color::White);
		draw(*window, sf::RenderStates::Default);
		window->draw(winOverlayLine);
		window->draw(anyKeyText);
		window->display();
	}
}

void Tic_Tac_Toe::ResetBoard()
{
	for (auto &s : board)
	{
		s = "-";
	}
	playerTurn = false;
	gameOver = false;
	anyKeyPressed = false;

	window->clear(sf::Color::White);
	for (auto &box : boxes)
		box.setTexture(nullptr);
}

void Tic_Tac_Toe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto box : boxes)
		target.draw(box);
	for (auto line : lines)
		target.draw(line);
}

void Tic_Tac_Toe::CreateBoard()
{
	int x = 30;
	int y = 30;
	int counter = 0;
	for (auto& box : boxes)
	{
		box.setSize(sf::Vector2f(window->getSize().x / 5, window->getSize().y / 5));
		box.setTexture(nullptr);
		box.setOutlineThickness(0);
		box.setPosition(sf::Vector2f(x, y));

		if (counter < 2)
		{
			x += 200;
			++counter;
		}
		else
		{
			x = 30;
			y += 200;
			counter = 0;
		}
	}

	// Horizontal lines
	lines.at(0).setSize(sf::Vector2f(580, 15));
	lines.at(0).setPosition(sf::Vector2f(10, 175));
	lines.at(0).setFillColor(sf::Color::Black);

	lines.at(1).setSize(sf::Vector2f(580, 15));
	lines.at(1).setPosition(sf::Vector2f(10, 375));
	lines.at(1).setFillColor(sf::Color::Black);

	// Vertical lines
	lines.at(2).setSize(sf::Vector2f(580, 15));
	lines.at(2).setPosition(sf::Vector2f(195, 10));
	lines.at(2).rotate(90);
	lines.at(2).setFillColor(sf::Color::Black);

	lines.at(3).setSize(sf::Vector2f(580, 15));
	lines.at(3).setPosition(sf::Vector2f(395, 10));
	lines.at(3).rotate(90);
	lines.at(3).setFillColor(sf::Color::Black);

	winOverlayLine.setSize(sf::Vector2f(0, 10));
	winOverlayLine.setFillColor(sf::Color::Red);
	
	anyKeyText.setFont(font);
	anyKeyText.setFillColor(sf::Color(150, 150, 0));
	anyKeyText.setString("Press any	key to    continue..");
	anyKeyText.setPosition(sf::Vector2f(1, 550));
}

void Tic_Tac_Toe::LoadResources()
{
	if (!cross.loadFromFile("Images\\X.png"))
	{
		std::cerr << "Load cross texture error!" << '\n';
	}
	if (!circle.loadFromFile("Images\\O.png"))
	{
		std::cerr << "Load circle texture error!" << '\n';
	}
	if (!font.loadFromFile("Font\\OCRAEXT.ttf"))
	{
		exit(EXIT_FAILURE);
	}
}

void Tic_Tac_Toe::HandleEvents()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				int counter = 0;
				for (auto& box : boxes)
				{
					if (box.getGlobalBounds().contains(mousePosF) && (board.at(counter) == "-"))
					{
						if (playerTurn)
						{
							board.at(counter) = "X";
							box.setTexture(&cross);
						}
						else
						{
							board.at(counter) = "O";
							box.setTexture(&circle);
						}

						playerTurn = !playerTurn;
					}
					++counter;
				}
			}
		}
		if (event.type == sf::Event::KeyPressed && gameOver == true)
			anyKeyPressed = true;
	}
}

bool Tic_Tac_Toe::GameCondition()
{
	// Horizontal
	for (int i = 0; i < 3; ++i)
	{
		if (Equals3(board.at(i * 3), board.at(i * 3 + 1), board.at(i * 3 + 2)))
		{
			DrawWinningLine(boxes.at(i *  3), boxes.at(i * 3 + 2), 0, false, false);
			gameOver = true;
			break;
		}
	}
	// Vertical
	for (int j = 0; j < 3; ++j)
	{
		if (Equals3(board.at(j), board.at(j + 3), board.at(j + 6)))
		{
			DrawWinningLine(boxes.at(j), boxes.at(j + 6), 90, true, false);
			gameOver = true;
			break;
		}
	}
	// Diagonal
	if (Equals3(board.at(0), board.at(4), board.at(8)))
	{
		DrawWinningLine(boxes.at(0), boxes.at(8), 45, false, true);
		gameOver = true;
	}
	if (Equals3(board.at(2), board.at(4), board.at(6)))
	{
		DrawWinningLine(boxes.at(2), boxes.at(6), 135, false, true);
		gameOver = true;
	}

	return gameOver;
}

bool Tic_Tac_Toe::Equals3(const std::string &s1, const std::string &s2, const std::string &s3) const
{
	if ((s1 == s2) && (s1 == s3) && !(s1 == "-" ))
		return true;
	return false;
}

void Tic_Tac_Toe::DrawWinningLine(const sf::RectangleShape &r1, const sf::RectangleShape &r2, float angle, bool isVertical, bool isDiagonal)
{
	winOverlayLine.setRotation(0);
	// Get boxes' local center point
	sf::Vector2f boxCenter
	(
		(r1.getLocalBounds().left + r1.getLocalBounds().width) / 2.0f,
		(r1.getLocalBounds().top + r1.getLocalBounds().height) / 2.0f
	);
	// Convert local coords to global
	auto global = r1.getTransform().transformPoint(boxCenter);

	winOverlayLine.setPosition
	(
		sf::Vector2f
		(
			global.x, global.y
		)
	);

	if (!isVertical && !isDiagonal)
	{
		winOverlayLine.setSize
		(
			sf::Vector2f
			(
				r2.getGlobalBounds().left - r1.getGlobalBounds().left,
				winOverlayLine.getSize().y
			)
		);
	}
	else if(isVertical)
	{
		winOverlayLine.setSize
		(
			sf::Vector2f
			(
				r2.getGlobalBounds().top - r1.getGlobalBounds().top,
				winOverlayLine.getSize().y
			)
		);

		winOverlayLine.rotate(angle);
	}
	else
	{
		winOverlayLine.setSize
		(
			sf::Vector2f
			(
				r2.getGlobalBounds().top - r1.getGlobalBounds().top + 180,
				winOverlayLine.getSize().y
			)
		);

		winOverlayLine.rotate(angle);
	}
}
