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

	bool m_isDisplay;

	std::vector<sf::Sprite> m_heatlhStatus;
	std::vector<sf::RectangleShape> m_turnStatus;

	void display(ChessPiece* piece);

	void setHealthStatus(int health);
};