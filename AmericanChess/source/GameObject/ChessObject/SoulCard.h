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

private:
	sf::Sprite m_piece;
	PIECETYPE m_type;

	bool m_hasSoul;

	bool isHover();
	void handleClick();
};