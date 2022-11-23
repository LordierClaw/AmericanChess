#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "Board.h"

class InfoBox {
public:
	InfoBox();
	~InfoBox();

	void init();
	void update(float deltaTime);
	void render();

private:
	sf::Text m_heathLbl;
	sf::Text m_turnLbl;

	std::vector<sf::Text> m_gunInfoList;

	bool m_isDisplay;

	void display(ChessPiece* piece);
};