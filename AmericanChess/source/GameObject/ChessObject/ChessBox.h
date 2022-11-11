#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "../../GameConfig.h"
#include "ChessPosition.h"

class ChessBox : sf::RectangleShape {
public:
	ChessBox();
	ChessBox(sf::Vector2f size, ChessPosition pos);
	~ChessBox();

	bool isMouseHover();
	bool isMouseClick();

	ChessPosition getChessPosition();

	void render();

	void showOutline();
	void hideOutline();
private:
	ChessPosition m_chessPos;
	sf::Sprite m_outline;
	bool m_isVisible;
};