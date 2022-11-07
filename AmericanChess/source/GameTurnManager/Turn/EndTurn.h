#pragma once
#include "../GameTurnBase.h"
#include "../../GameStateManager/GameStateMachine.h"

class EndTurn : public GameTurnBase {
public:
	EndTurn();
	~EndTurn();

	void init();
	void update(float deltaTime);
	void render();
private:
	ChessPosition m_PlayerPosition;

	void handleClearBoard();
};