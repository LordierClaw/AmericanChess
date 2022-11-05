#include "GameTurnBase.h"
#include "Turn/ShowupTurn.h"
#include "Turn/PlayerTurn.h"
#include "Turn/BotTurn.h"

GameTurnBase::GameTurnBase() {
	isPerforming = false;
}

GameTurnBase::~GameTurnBase() {
}

GameTurnBase* GameTurnBase::createTurn(TURN turn) {
	GameTurnBase* gameTurn = nullptr;
	switch (turn) {
	case SHOWUP_TURN:
		gameTurn = new ShowupTurn();
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