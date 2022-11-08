#pragma once
#include "ChessBox.h"
#include "Shotgun.h"
#include "Player.h"
#include "SoulCard.h"
#include "../../GameTurnManager/GameTurnBase.h"
#include "../../GameTurnManager/GameTurnMachine.h"
#include <vector>

#define ChessBoard Board::GetInstance()

class InfoBox;

class Board : public sf::RectangleShape, public Singleton<Board> {
public:
	Board();
	~Board();
	void init();
	void update(float deltaTime);
	void render();

	Player* getPlayer();
	std::vector<ChessPiece*>& getChessList();
	ChessBox* getChessBox(int x, int y);

	SoulCard* getSoulCard();

private:
	Player* m_player;
	ChessPiece* m_king;

	std::vector<ChessPiece*> m_ChessList;
	ChessBox m_ChessTable[8][8];

	SoulCard* m_soulCard;
	InfoBox* m_infoBox;
};