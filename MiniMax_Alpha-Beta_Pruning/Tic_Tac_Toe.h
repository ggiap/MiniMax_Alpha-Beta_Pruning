#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

class Tic_Tac_Toe : public sf::Drawable
{
public:
	Tic_Tac_Toe() = default;
	Tic_Tac_Toe(sf::RenderWindow& window, bool playerTurn = false) : window(&window), playerTurn(playerTurn)
	{
		LoadResources();
		CreateBoard();
	}

	void StartGame(bool);
	void ResetBoard();
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	void CreateBoard();
	void LoadResources();
	void HandleEvents();
	bool GameCondition();
	bool Equals3(const std::string&, const std::string&, const std::string&) const;
	void DrawWinningTrio(std::vector<sf::RectangleShape*>&);
	int  Evaluate();
	int  MiniMax(int, bool);
	int  FindBestMove();

	sf::RenderWindow* window;
	std::vector<sf::RectangleShape> boxes{ 9, sf::RectangleShape() };
	sf::Texture cross;
	sf::Texture circle;
	sf::Texture redCross;
	sf::Texture redCircle;
	std::vector<sf::RectangleShape> lines{ 4, sf::RectangleShape() };
	sf::Font font;
	sf::Text anyKeyText;
	std::vector<std::string> board
	{
		"-", "-", "-",
		"-", "-", "-",
		"-", "-", "-"
	};
	bool playerTurn = false;
	bool gameOver = false;
	bool anyKeyPressed = false;
	bool onePlayerMode = false;
	bool playerClicked = false;
};

