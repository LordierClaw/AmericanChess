#pragma once
#include "../GameTurnBase.h"

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

	MousePos getPlayerIntention();

	void hideNearbyBox();

	void handlePlayerEvent();
	void handleMoveEvent();
	void handleShootEvent();
};