#include "Tic_Tac_Toe.h"


void Tic_Tac_Toe::StartGame(bool mode)
{
	playerClicked = true;
	onePlayerMode = mode;

	while (!gameOver)
	{
		if (onePlayerMode)
		{
			if (!gameOver && playerClicked)
			{
				int pos = FindBestMove();
				board.at(pos) = "X";
				boxes.at(pos).getRect().setTexture(&cross);
				boxes.at(pos).isPressed = true;

				playerTurn = !playerTurn;
				playerClicked = false;
			}
		}
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
		window->draw(anyKeyText);
		window->display();
	}
}

void Tic_Tac_Toe::ResetBoard()
{
	for (auto& s : board)
	{
		s = "-";
	}
	gameOver = false;
	anyKeyPressed = false;

	window->clear(sf::Color::White);
	for (auto& box : boxes)
	{
		box.getRect().setTexture(nullptr);
		box.getRect().setFillColor(sf::RectangleShape().getFillColor());
		box.isPressed = false;
	}

	playerTurn = false;
	onePlayerMode = false;
	playerClicked = false;
}

void Tic_Tac_Toe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& box : boxes)
		target.draw(box.getRect());
	for (const auto& line : lines)
		target.draw(line);
}

void Tic_Tac_Toe::CreateBoard()
{
	int x = 30;
	int y = 30;
	int counter = 0;
	for (auto &box : boxes)
	{
		box.getRect().setSize(sf::Vector2f(window->getSize().x / 5, window->getSize().y / 5));
		
		box.getRect().setOutlineThickness(0);
		box.getRect().setPosition(sf::Vector2f(x, y));

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

	counter = 0;
	for (auto &s : board)
	{
		if (s == "-")
			boxes.at(counter).getRect().setTexture(nullptr);
		else if (s == "X")
			boxes.at(counter).getRect().setTexture(&cross);
		else
			boxes.at(counter).getRect().setTexture(&circle);

		++counter;
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
						if (box.getRect().getGlobalBounds().contains(mousePosF) && (board.at(counter) == "-"))
						{			
							box.isPressed = true;
							if (onePlayerMode)
							{
								board.at(counter) = "O";
								box.getRect().setTexture(&circle);

								playerClicked = true;
								playerTurn = !playerTurn;
								gameOver = GameCondition();

								break;
							}
							else
							{
								if (playerTurn)
								{
									board.at(counter) = "X";
									box.getRect().setTexture(&cross);
								}
								else
								{
									board.at(counter) = "O";
									box.getRect().setTexture(&circle);
								}

								playerTurn = !playerTurn;
								break;
							}
						}
						++counter;
					}
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				for (auto& box : boxes)
				{
					if (box.getRect().getGlobalBounds().contains(mousePosF) && !box.isPressed)
					{
						box.getRect().setFillColor(sf::Color(25, 100, 150, 255));
						break;
					}
					else
					{
						box.getRect().setFillColor(sf::RectangleShape().getFillColor());
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
	std::vector<Button*> winningTrio;

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
		return true;
}

bool Tic_Tac_Toe::Equals3(const std::string& s1, const std::string& s2, const std::string& s3) const
{
	if ((s1 == s2) && (s1 == s3) && !(s1 == "-"))
		return true;
	return false;
}

void Tic_Tac_Toe::DrawWinningTrio(std::vector<Button*>& winningTrio)
{
	for (auto& box : winningTrio)
	{
		box->getRect().setFillColor(sf::RectangleShape().getFillColor());
		if (onePlayerMode)
		{
			if (!playerTurn)
				box->getRect().setTexture(&redCircle);
			else
				box->getRect().setTexture(&redCross);
		}
		else
		{
			if (playerTurn)
				box->getRect().setTexture(&redCircle);
			else
				box->getRect().setTexture(&redCross);
		}
	}
}

int Tic_Tac_Toe::Evaluate()
{
	// Diagonal
	if (Equals3(board.at(0), board.at(4), board.at(8)))
	{
		if (playerTurn)
			return 10;
		else
			return -10;
	}
	if (Equals3(board.at(2), board.at(4), board.at(6)))
	{
		if (playerTurn)
			return 10;
		else
			return -10;
	}

	// Horizontal
	for (int i = 0; i < 3; ++i)
	{
		if (Equals3(board.at(i * 3), board.at(i * 3 + 1), board.at(i * 3 + 2)))
		{
			if (playerTurn)
				return 10;
			else
				return -10;
		}
	}
	// Vertical
	for (int j = 0; j < 3; ++j)
	{
		if (Equals3(board.at(j), board.at(j + 3), board.at(j + 6)))
		{
			if (playerTurn)
				return 10;
			else
				return -10;
		}
	}

	return 0;
}

int Tic_Tac_Toe::Alpha_Beta(int depth, bool isMaximize, int a, int b)
{
	int score = Evaluate();

	if (score == 10)
		return score;

	if (score == -10)
		return score;

	if (depth == 0)
		return score;

	if (std::find(board.begin(), board.end(), "-") == board.end())
		return score;

	if (isMaximize)
	{
		int best = std::numeric_limits<int>::min();
		for (auto& s : board)
		{
			if (s == "-")
			{
				s = "X";

				playerTurn = !playerTurn;

				best = std::max(best, Alpha_Beta(depth - 1, false, a, b));
				a = max(a, best);

				playerTurn = !playerTurn;

				s = "-";

				if (a >= b)
					break;
			}
		}
		return best;
	}
	else
	{
		int best = std::numeric_limits<int>::max();
		for (auto& s : board)
		{
			if (s == "-")
			{
				s = "O";

				playerTurn = !playerTurn;

				best = std::min(best, Alpha_Beta(depth - 1, true, a, b));
				b = min(b, best);

				playerTurn = !playerTurn;

				s = "-";

				if (a >= b)
					break;
			}
		}
		return best;
	}
}

int Tic_Tac_Toe::MiniMax(int depth, bool isMaximize)
{
	int score = Evaluate();

	if (score == 10)
		return score;

	if (score == -10)
		return score;

	if (depth == 0)
		return score;

	if (std::find(board.begin(), board.end(), "-") == board.end())
		return score;

	if (isMaximize)
	{
		int best = INT32_MIN;
		for (auto& s : board)
		{
			if (s == "-")
			{
				s = "X";
				playerTurn = !playerTurn;
				best = std::max(best, MiniMax(depth - 1, false));
				playerTurn = !playerTurn;
				s = "-";
			}
		}
		return best;
	}
	else
	{
		int best = INT32_MAX;
		for (auto& s : board)
		{
			if (s == "-")
			{
				s = "O";
				playerTurn = !playerTurn;
				best = std::min(best, MiniMax(depth - 1, true));
				playerTurn = !playerTurn;
				s = "-";
			}
		}
		return best;
	}
}

int Tic_Tac_Toe::FindBestMove()
{
	int bestValue = std::numeric_limits<int>::min();
	int pos = -1;
	int counter = 0;

	for (auto &s : board)
	{
		if (s == "-")
		{
			s = "X";

			playerTurn = !playerTurn;

			//int moveValue = MiniMax(15, false);
			int moveValue = Alpha_Beta(15, false,
				std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

			playerTurn = !playerTurn;

			s = "-";

			if (moveValue > bestValue)
			{
				bestValue = moveValue;
				pos = counter;
			}
		}
		++counter;
	}
	return pos;
}
