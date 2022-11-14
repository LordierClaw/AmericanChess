#pragma once
#include "../GameTurnBase.h"
#include "../../GameStateManager/GameStateMachine.h"

class WinTurn : public GameTurnBase {
public:
	WinTurn();
	~WinTurn();

	void init();
	void update(float deltaTime);
	void render();
private:
	ChessPosition m_PlayerPosition;

	void handleClearBoard();
};