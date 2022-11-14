#pragma once
#include "../GameTurnBase.h"
#include "../../Misc/ChessMoveGenerator.h"

class BotTurn : public GameTurnBase {
public:
	BotTurn();
	~BotTurn();

	void init();
	void update(float deltaTime);
	void render();

private:
	ChessPosition m_PlayerPosition;

	bool isEndBotTurn();
	void handleBotEvent();

	bool m_isPlayerKillable;
};