#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Tic_Tac_Toe : public sf::Drawable
{
public:
	Tic_Tac_Toe() = default;
	Tic_Tac_Toe(sf::RenderWindow &window, bool playerTurn = false) : window(&window), playerTurn(playerTurn) 
	{
		LoadResources();
		CreateBoard();
	}
	
	void StartGame();
	void ResetBoard();
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	void CreateBoard();
	void LoadResources();
	void HandleEvents();
	bool GameCondition();
	bool Equals3(const std::string&, const std::string&, const std::string&) const;
	void DrawWinningLine(const sf::RectangleShape&, const sf::RectangleShape&, float, bool, bool);

	sf::RenderWindow *window;
	std::vector<sf::RectangleShape> boxes{ 9, sf::RectangleShape() };
	sf::Texture cross;
	sf::Texture circle;
	std::vector<sf::RectangleShape> lines{ 4, sf::RectangleShape() };
	sf::RectangleShape winOverlayLine;
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
};

