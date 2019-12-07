#include "Tic_Tac_Toe.h"

void Tic_Tac_Toe::StartGame(bool mode, bool whoPlaysFirst, bool algorithmChoice, int diff)
{
	playerTurn = whoPlaysFirst;
	onePlayerMode = mode;
	algChoice = algorithmChoice;
	depth = diff;

	while (!gameOver)
	{
		if (onePlayerMode)
		{
			if (!gameOver && (playerClicked || !playerTurn))
			{
				int pos = FindBestMove();
				if (playerTurn)
				{
					board.at(pos) = playerSymbol;
					boxes.at(pos).getRect().setTexture(&cross);
				}
				else
				{
					board.at(pos) = opponentSymbol;
					boxes.at(pos).getRect().setTexture(&circle);
				}
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

		if (backButton.isPressed)
			gameOver = true;
	}

	backButton.ResetButtonState();

	while (!backButton.isPressed)
	{
		HandleEvents();

		window->clear(sf::Color::White);
		draw(*window, sf::RenderStates::Default);
		window->draw(pressAgainText);
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

	window->clear(sf::Color::White);
	for (auto& box : boxes)
	{
		box.getRect().setTexture(nullptr);
		box.getRect().setFillColor(sf::RectangleShape().getFillColor());
		box.ResetButtonState();
	}

	backButton.ResetButtonState();

	onePlayerMode = false;
	playerClicked = false;
	count = 0;
}

void Tic_Tac_Toe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& box : boxes)
		target.draw(box.getRect());
	for (const auto& line : lines)
		target.draw(line);

	target.draw(backButton);
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
		else if (s == playerSymbol)
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

	pressAgainText.setFont(font);
	pressAgainText.setFillColor(sf::Color(150, 150, 0));
	pressAgainText.setString("   Press    back to    exit..");
	pressAgainText.setPosition(sf::Vector2f(1, 550));

	backButton.buttonConfig(sf::Vector2f(65, 30), sf::Vector2f(535, 570), sf::Color(50, 100, 200, 95), sf::Color::Black, "Back");
	backButton.setHoverColor(ORANGE);
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

		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		if (!gameOver)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int counter = 0;
					for (auto& box : boxes)
					{
						if (box.getRect().getGlobalBounds().contains(mousePosF) && (board.at(counter) == "-"))
						{			
							box.isPressed = true;
							if (onePlayerMode)
							{
								if (playerTurn)
								{
									board.at(counter) = playerSymbol;
									box.getRect().setTexture(&cross);
								}
								else
								{
									board.at(counter) = opponentSymbol;
									box.getRect().setTexture(&circle);
								}

								playerTurn = !playerTurn;
								playerClicked = true;
								gameOver = GameCondition();

								break;
							}
							else
							{
								if (playerTurn)
								{
									board.at(counter) = playerSymbol;
									box.getRect().setTexture(&cross);
								}
								else
								{
									board.at(counter) = opponentSymbol;
									box.getRect().setTexture(&circle);
								}

								playerTurn = !playerTurn;
								break;
							}
						}
						++counter;
					}

					if (backButton.getRect().getGlobalBounds().contains(mousePosF))
						backButton.isPressed = true;
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
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

				if (backButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					backButton.setButtonTextColor(backButton.getHoverColor());
				}
				else
				{
					backButton.setButtonTextColor(sf::Color::Black);
				}
			}
		}

		if (gameOver)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (backButton.getRect().getGlobalBounds().contains(mousePosF))
						backButton.isPressed = true;
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				if (backButton.getRect().getGlobalBounds().contains(mousePosF))
				{
					backButton.setButtonTextColor(backButton.getHoverColor());
				}
				else
				{
					backButton.setButtonTextColor(sf::Color::Black);
				}
			}
		}
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

	return false;
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

		if (playerTurn)
			box->getRect().setTexture(&redCircle);
		else
			box->getRect().setTexture(&redCross);
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

	++count;

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
				if (playerTurn)
					s = playerSymbol;
				else
					s = opponentSymbol;

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
				if (playerTurn)
					s = playerSymbol;
				else
					s = opponentSymbol;

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

	++count;

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
				if (playerTurn)
					s = playerSymbol;
				else
					s = opponentSymbol;

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
				if (playerTurn)
					s = playerSymbol;
				else
					s = opponentSymbol;

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

	count = 0;
	// Used for debugging
	t1 = std::chrono::high_resolution_clock::now();
	for (auto &s : board)
	{
		if (s == "-")
		{
			if (playerTurn)
				s = playerSymbol;
			else
				s = opponentSymbol;

			playerTurn = !playerTurn;

			int moveValue = 0;

			if (algChoice)
				moveValue = MiniMax(depth, false);
			else
				moveValue = Alpha_Beta(depth, false,
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
	// Used for debugging
	t2 = chrono::high_resolution_clock::now();
	time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	std::cout << count << "\t" << time_span.count() << '\n';

	return pos;
}
