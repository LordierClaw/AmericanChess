#pragma once
#include "../GameManager/ResourceManager.h"
#include "../GameManager/WindowConnector.h"
#include "../GameObject/ChessObject/Board.h"
#include "GameTurnMachine.h"

class GameTurnBase {
public:
	GameTurnBase();
	virtual ~GameTurnBase();

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

	static GameTurnBase* createTurn(TURN turn);
protected:
	bool isPerforming;
};