#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>

#include "Button.h"

class Tic_Tac_Toe : public sf::Drawable
{
public:
	Tic_Tac_Toe() = default;
	Tic_Tac_Toe(sf::RenderWindow& window, bool playerTurn = false) : window(&window), playerTurn(playerTurn)
	{
		LoadResources();
		CreateBoard();
	}

	void StartGame(bool, bool, bool, int);
	void ResetBoard();
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	void CreateBoard();
	void LoadResources();
	void HandleEvents();
	bool GameCondition();
	bool Equals3(const std::string&, const std::string&, const std::string&) const;
	void DrawWinningTrio(std::vector<Button*>&);
	int  Evaluate();
	int  Alpha_Beta(int, bool, int, int);
	int  MiniMax(int, bool);
	int  FindBestMove();

	sf::RenderWindow* window;
	std::vector<Button> boxes{ 9, Button() };
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
	const std::string playerSymbol = "X";
	const std::string opponentSymbol = "O";
	bool playerTurn = false;
	bool gameOver = false;
	bool anyKeyPressed = false;
	bool onePlayerMode = false;
	bool playerClicked = false;
	bool algChoice = false;
	int depth = 0;

	// Used for debugging purposes
	int count = 0;
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	chrono::duration<double> time_span;
};

