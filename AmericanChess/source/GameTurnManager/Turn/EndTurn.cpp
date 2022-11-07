#include "EndTurn.h"

EndTurn::EndTurn() {
}

EndTurn::~EndTurn() {
}

void EndTurn::init() {
	std::cout << "Start of End Turn" << '\n';
	ChessBoard->getPlayer()->getGun()->setShootable(false);
	m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
	for (auto piece : ChessBoard->getChessList()) {
		if (piece->getType() != PIECETYPE::PLAYER) {
			piece->setShootPosition(m_PlayerPosition);
			piece->changeState(KILL);
			piece->performTurn();
		}
	}
}

void EndTurn::update(float deltaTime) {
	if (ChessBoard->getChessList().size() == 1) {
		std::cout << "End of End Turn" << '\n';
		GSM->changeState(INTRO);
		return;
	}
	for (auto piece : ChessBoard->getChessList()) {
		piece->update(deltaTime);
	}
	handleClearBoard();
}

void EndTurn::render() {
	for (auto piece : ChessBoard->getChessList()) {
		piece->render();
	}
}

void EndTurn::handleClearBoard() {
	for (int i = 0; i < ChessBoard->getChessList().size(); i++) {
		if (ChessBoard->getChessList()[i]->getState() == STATE::DEAD) {
			delete ChessBoard->getChessList()[i];
			ChessBoard->getChessList().erase(ChessBoard->getChessList().begin() + i);
			i--;
		}
	}
}
