#include "GameTurnMachine.h"
#include "GameTurnBase.h"

GameTurnMachine::GameTurnMachine() {
	m_TurnCount = -1; //showing up turn will start at 0
	m_CurrentTurn = nullptr;
	m_NextTurn = nullptr;
}

GameTurnMachine::~GameTurnMachine() {
	if (m_CurrentTurn != nullptr) delete m_CurrentTurn;
	if (m_NextTurn != nullptr) delete m_NextTurn;
}

void GameTurnMachine::changeTurn(GameTurnBase* turn) {
	m_NextTurn = turn;
}

void GameTurnMachine::changeTurn(TURN turn) {
	GameTurnBase* gameTurn = GameTurnBase::createTurn(turn);
	changeTurn(gameTurn);
}

void GameTurnMachine::performTurnChange() {
	m_TurnCount++;
	if (m_NextTurn != nullptr) {
		GameTurnBase* oldTurn = m_CurrentTurn;
		m_CurrentTurn = m_NextTurn;
		m_CurrentTurn->init();
		if (oldTurn != nullptr) delete oldTurn;
		m_NextTurn = nullptr;
	}
}

GameTurnBase* GameTurnMachine::currentTurn() const {
	return m_CurrentTurn;
}

GameTurnBase* GameTurnMachine::nextTurn() const {
	return m_NextTurn;
}

bool GameTurnMachine::needToChangeTurn() {
	return m_NextTurn != nullptr;
}

int GameTurnMachine::getTurnCount() {
	return m_TurnCount;
}

void GameTurnMachine::resetCount() {
	m_TurnCount = -1;
}
