#include "ShowupTurn.h"

ShowupTurn::ShowupTurn() {
}

ShowupTurn::~ShowupTurn() {
}

void ShowupTurn::init() {
	std::cout << "Start of Showing up Turn\n";
	ChessBoard->getPlayer()->getGun()->setShootable(false);
	for (auto piece : ChessBoard->getChessList()) {
		piece->performTurn();
	}
	isPerforming = false;
	m_currentTime = 0;
}

void ShowupTurn::update(float deltaTime) {
	if (isPerforming == false) {
		if (ChessBoard->getPlayer()->isEndTurn() == false) {
			this->handlePlayerShowUp(deltaTime);
		} else {
			this->handleBotShowUp(deltaTime);
		}
	} else {
		std::cout << "End of Showing up Turn\n";
		GTM->changeTurn(PLAYER_TURN);
	}
}

void ShowupTurn::render() {
	for (auto piece : ChessBoard->getChessList()) {
		piece->render();
	}
}

void ShowupTurn::handlePlayerShowUp(float deltaTime) {
	ChessBoard->getPlayer()->update(deltaTime);
}

void ShowupTurn::handleBotShowUp(float deltaTime) {
	m_currentTime += deltaTime;
	int nPiece = ChessBoard->getChessList().size() - 1;
	int i = 0, endCount = 0;
	for (auto piece : ChessBoard->getChessList()) {
		if (piece->getType() != PIECETYPE::PLAYER) {
			if (m_currentTime >= SHOW_UP_DURATION / 2 * i) {
				piece->update(deltaTime);
				if (piece->isEndTurn()) endCount++;
			}
			i++;
		}
	}
	if (endCount == nPiece) isPerforming = true;
}
