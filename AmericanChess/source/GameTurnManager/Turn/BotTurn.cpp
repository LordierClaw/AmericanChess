#include "BotTurn.h"

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
    m_isPlayerKillable = false;
    m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
}

void BotTurn::update(float deltaTime) {
    if (m_isPlayerKillable) GTM->changeTurn(TURN::LOSE_TURN);

    if (isPerforming == false) {
        handleBotEvent();
    } else {
        if (this->isEndBotTurn()) {
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
    for (auto piece : ChessBoard->getChessList()) {
        if (piece->getType() != PIECETYPE::PLAYER) {
            if (piece->getTurnLeft() == 0) {
                ChessPosition pos = piece->getCurrentPosition();
                //gen move
                std::cout << "A piece want to move from " << pos.x << "-" << pos.y << " to ";
                pos = MoveGen->getNextMove(piece);
                std::cout << pos.x << "-" << pos.y << '\n';
                //if piece kill player
                if (pos == m_PlayerPosition) {
                    std::cout << "Black King is going to DIE\n";
                    m_isPlayerKillable = true;
                }
                //promote
                if (piece->getType() == PIECETYPE::PAWN && pos != m_PlayerPosition && pos.y == 7) {
                    piece->setPromotion(true);
                }
                //set move
                piece->setDestPosition(pos);
                piece->changeState(STATE::MOVING);
                piece->performTurn();
            }
        }
    }
    isPerforming = true;
}
