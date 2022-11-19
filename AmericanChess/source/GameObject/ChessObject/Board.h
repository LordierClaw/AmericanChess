#pragma once
#include "ChessBox.h"
#include "SoulCard.h"
#include "GunAmmoBox.h"
#include "CashCounter.h"
#include "../../GameTurnManager/GameTurnBase.h"
#include "../../GameTurnManager/GameTurnMachine.h"
#include "../GameRuleManager.h"
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

	void setLevel(int level);
	
	Player* getPlayer();
	std::vector<ChessPiece*>& getChessList();
	ChessBox* getChessBox(int x, int y);

	SoulCard* getSoulCard();

	void disableBoard();
	void enableBoard();

private:
	bool m_isEnable;

	Player* m_player;

	std::vector<ChessPiece*> m_ChessList;
	ChessBox m_ChessTable[8][8];

	SoulCard* m_soulCard;
	InfoBox* m_infoBox;
	GunAmmoBox* m_ammoBox;
};