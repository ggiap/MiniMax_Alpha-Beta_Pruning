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
	gameOver = false;
	anyKeyPressed = false;

	window->clear(sf::Color::White);
	for (auto &box : boxes)
		box.setTexture(nullptr);

	winOverlayLine.setFillColor(sf::Color(255, 215, 0));
}

void Tic_Tac_Toe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto &box : boxes)
		target.draw(box);
	for (const auto &line : lines)
		target.draw(line);
}

void Tic_Tac_Toe::CreateBoard()
{
	int x = 30;
	int y = 30;
	int counter = 0;
	for (auto &box : boxes)
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
	winOverlayLine.setFillColor(sf::Color(255, 215, 0));
	
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
	if (!redCross.loadFromFile("Images\\XR.png"))
	{
		std::cerr << "Load cross texture error!" << '\n';
	}
	if (!redCircle.loadFromFile("Images\\OR.png"))
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
		if (!gameOver)
		{
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
		}
		if (event.type == sf::Event::KeyPressed && gameOver == true)
			anyKeyPressed = true;
	}
}

bool Tic_Tac_Toe::GameCondition()
{
	std::vector<sf::RectangleShape*> winningTrio;

	// Diagonal
	if (Equals3(board.at(0), board.at(4), board.at(8)))
	{
		winningTrio.push_back(&boxes.at(0));
		winningTrio.push_back(&boxes.at(4));
		winningTrio.push_back(&boxes.at(8));
		DrawWinningTrio(winningTrio);
		
		return true;
	}
	if (Equals3(board.at(2), board.at(4), board.at(6)))
	{
		winningTrio.push_back(&boxes.at(2));
		winningTrio.push_back(&boxes.at(4));
		winningTrio.push_back(&boxes.at(6));
		DrawWinningTrio(winningTrio);

		return true;
	}

	// Horizontal
	for (int i = 0; i < 3; ++i)
	{
		if (Equals3(board.at(i * 3), board.at(i * 3 + 1), board.at(i * 3 + 2)))
		{
			winningTrio.push_back(&boxes.at(i * 3));
			winningTrio.push_back(&boxes.at(i * 3 + 1));
			winningTrio.push_back(&boxes.at(i * 3 + 2));
			DrawWinningTrio(winningTrio);
			
			return true;
		}
	}
	// Vertical
	for (int j = 0; j < 3; ++j)
	{
		if (Equals3(board.at(j), board.at(j + 3), board.at(j + 6)))
		{
			winningTrio.push_back(&boxes.at(j));
			winningTrio.push_back(&boxes.at(j + 3));
			winningTrio.push_back(&boxes.at(j + 6));
			DrawWinningTrio(winningTrio);

			return true;
		}
	}	

	if (std::find(board.begin(), board.end(), "-") == board.end())
	{
		winOverlayLine.setFillColor(sf::Color(255, 215, 0,0));

		return true;
	}
}

bool Tic_Tac_Toe::Equals3(const std::string &s1, const std::string &s2, const std::string &s3) const
{
	if ((s1 == s2) && (s1 == s3) && !(s1 == "-" ))
		return true;
	return false;
}

void Tic_Tac_Toe::DrawWinningTrio(std::vector<sf::RectangleShape*> &winningTrio)
{
	for(auto &box : winningTrio)
	if (playerTurn)
		box->setTexture(&redCircle);
	else
		box->setTexture(&redCross);
}
