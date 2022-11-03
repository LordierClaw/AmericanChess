#include "GameTurnBase.h"
#include "Turn/PlayerTurn.h"
#include "Turn/BotTurn.h"

GameTurnBase::GameTurnBase() {
}

GameTurnBase::~GameTurnBase() {
}

GameTurnBase* GameTurnBase::createTurn(TURN turn) {
	GameTurnBase* gameTurn = nullptr;
	switch (turn) {
	case SHOWUP:
		break;
	case PLAYER_TURN:
		gameTurn = new PlayerTurn();
		break;
	case BOT_TURN:
		gameTurn = new BotTurn();
		break;
	case END_BOARD:
		break;
	default:
		break;
	}
	return gameTurn;
}