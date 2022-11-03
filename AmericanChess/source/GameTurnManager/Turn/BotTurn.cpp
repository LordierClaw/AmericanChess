#include "BotTurn.h"
#include <cstdlib>

BotTurn::BotTurn() {
}

BotTurn::~BotTurn() {
}

void BotTurn::init() {
    std::cout << "Start of Bot Turn" << '\n';
    for (auto piece : ChessBoard->getChessList()) {
        piece->endTurn();
    }
    ChessBoard->getPlayer()->getGun()->setShootable(false);
    isPerforming = false;
}

void BotTurn::update(float deltaTime) {
    if (isPerforming == false) {
        handleBotEvent();
    } else {
        if (this->isEndBotTurn()) {
            for (auto piece : ChessBoard->getChessList()) {
                piece->countTurnLeft();
            }
            std::cout << "End of Bot Turn" << '\n';
            GTM->changeTurn(TURN::PLAYER_TURN);
        }
    }

    for (auto piece : ChessBoard->getChessList()) {
        piece->update(deltaTime);
    }
}

void BotTurn::render() {
    for (auto piece : ChessBoard->getChessList()) {
        piece->render();
    }
}

bool BotTurn::isEndBotTurn() {
    for (auto piece : ChessBoard->getChessList()) {
        if (piece->getType() != PIECETYPE::PLAYER) {
            if (piece->isEndTurn() == false) return false;
        }
    }
    return true;
}

void BotTurn::handleBotEvent() {
    srand(time(NULL));

    for (auto piece : ChessBoard->getChessList()) {
        if (piece->getType() != PIECETYPE::PLAYER) {
            if (piece->getTurnLeft() == 0) {
                ChessPosition pos = piece->getCurrentPosition();
                std::cout << "A piece want to move from " << pos.x << "-" << pos.y << " to ";
                pos.x = rand() % 8;
                pos.y = rand() % 8;
                std::cout << pos.x << "-" << pos.y << '\n';
                piece->setDestPosition(pos);
                piece->changeState(STATE::MOVING);
                piece->performTurn();
            }
        }
    }
    isPerforming = true;
}
