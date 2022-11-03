#include "GameTurnMachine.h"
#include "GameTurnBase.h"

int GameTurnMachine::TURNCOUNT = 0;

GameTurnMachine::GameTurnMachine() {
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
	TURNCOUNT++;
	if (m_NextTurn != nullptr) {
		std::cout << "Turn: " << TURNCOUNT << "  ";
		GameTurnBase* oldTurn = m_CurrentTurn;
		std::cout << "OldTurn = " << oldTurn << "  ";
		m_CurrentTurn = m_NextTurn;
		std::cout << "CurrentTurn = " << m_CurrentTurn << '\n';
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