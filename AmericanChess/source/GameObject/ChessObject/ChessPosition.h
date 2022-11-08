#pragma once
#include "SFML/Graphics.hpp"

class ChessPosition {
public:
	int x, y;

	ChessPosition();
	ChessPosition(int x, int y);
	~ChessPosition();

	//convert x, y on board to Window Position
	sf::Vector2f toPosition();

	friend bool operator < (ChessPosition pos1, ChessPosition pos2);
	friend bool operator > (ChessPosition pos1, ChessPosition pos2);
	friend bool operator == (ChessPosition pos1, ChessPosition pos2);
	friend bool operator != (ChessPosition pos1, ChessPosition pos2);
};