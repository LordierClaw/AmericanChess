#include "WinTurn.h"

WinTurn::WinTurn() {
}

WinTurn::~WinTurn() {
}

void WinTurn::init() {
	ChessBoard->getPlayer()->getGun()->setShootable(false);
	m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
	for (auto piece : ChessBoard->getChessList()) {
		if (piece->getType() != PIECETYPE::PLAYER) {
			piece->setShootPosition(m_PlayerPosition);
			piece->changeState(KILL);
			piece->performTurn();
		}
	}

	GTM->resetCount();
}

void WinTurn::update(float deltaTime) {
	if (ChessBoard->getChessList().size() == 1) {
		if (GameRule->getCurrentLevel() == FINAL_LEVEL) GSM->changeState(END);
		else GSM->changeState(UPGRADE);
		return;
	}
	for (auto piece : ChessBoard->getChessList()) {
		piece->update(deltaTime);
	}
	handleClearBoard();
}

void WinTurn::render() {
	for (auto piece : ChessBoard->getChessList()) {
		piece->render();
	}
}

void WinTurn::handleClearBoard() {
	for (int i = 0; i < ChessBoard->getChessList().size(); i++) {
		if (ChessBoard->getChessList()[i]->getState() == STATE::DEAD) {
			delete ChessBoard->getChessList()[i];
			ChessBoard->getChessList().erase(ChessBoard->getChessList().begin() + i);
			i--;
		}
	}
}
