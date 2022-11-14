#include "GameTurnBase.h"
#include "Turn/ShowupTurn.h"
#include "Turn/PlayerTurn.h"
#include "Turn/BotTurn.h"
#include "Turn/WinTurn.h"
#include "Turn/LoseTurn.h"

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
	case WIN_TURN:
		gameTurn = new WinTurn();
		break;
	case LOSE_TURN:
		gameTurn = new LoseTurn();
	default:
		break;
	}
	return gameTurn;
}