#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "ChessPiece.h"

class SoulCard : public sf::RectangleShape {
public:
	SoulCard();
	~SoulCard();

	void init();
	void update(float deltaTime);
	void render();

	void setPiece(PIECETYPE type);
	PIECETYPE getPiece();
	void reset();

	bool isHover();
	bool hasSoul();

private:
	sf::Sprite m_piece;
	PIECETYPE m_type;
	sf::Text m_title;

	bool m_hasSoul;
};