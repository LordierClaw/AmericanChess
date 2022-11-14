#pragma once
#include "../GameTurnBase.h"
#include "../../Misc/ChessMoveGenerator.h"

enum MousePos {
	WANT_TO_MOVE = 0,
	WANT_TO_SHOOT,
	OUT_OF_BOARD,
	OUT_OF_WINDOW
};

class PlayerTurn : public GameTurnBase {
public:
	PlayerTurn();
	~PlayerTurn();

	void init();
	void update(float deltaTime);
	void render();

private:
	ChessPosition m_PlayerPosition;

	std::vector<ChessPosition> m_moveList;

	bool isEndPlayerTurn();

	MousePos m_playerIntent;
	MousePos getPlayerIntention();

	void hideNearbyBox();

	void handlePlayerEvent();
	void handleMoveEvent();

	void handleShootEvent();
	void handleBulletHitbox();
	bool handleKillPiece(); //return 1 if White King is dead, 0 is default
	
	//call before endturn;
	bool handleCheckKing();

	bool useSoulCard;
	void handleSoulCardEvent(PIECETYPE type);
};