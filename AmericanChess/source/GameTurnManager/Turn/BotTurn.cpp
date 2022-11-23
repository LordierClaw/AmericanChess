#include "BotTurn.h"

BotTurn::BotTurn() {
    m_isPlayerKillable = false;
}

BotTurn::~BotTurn() {
}

void BotTurn::init() {
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
                pos = MoveGen->getNextMove(piece);
                if (pos == piece->getCurrentPosition()) continue;
                //if piece kill player
                if (pos == m_PlayerPosition) {
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
