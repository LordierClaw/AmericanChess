#pragma once
#include "../GameTurnBase.h"

class ShowupTurn : public GameTurnBase {
public:
	ShowupTurn();
	~ShowupTurn();

	void init();
	void update(float deltaTime);
	void render();

private:
	ChessPosition m_PlayerPosition;

	void handlePlayerShowUp(float deltaTime);
	void handleBotShowUp(float deltaTime);
};