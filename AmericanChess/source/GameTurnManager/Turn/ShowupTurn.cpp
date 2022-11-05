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
	int i = 0;
	for (auto piece : ChessBoard->getChessList()) {
		piece->update(deltaTime);
		if (piece->isEndTurn()) i++;
	}
	if (i == ChessBoard->getChessList().size()) isPerforming = true;
}
