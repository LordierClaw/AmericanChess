#include "PlayerTurn.h"

PlayerTurn::PlayerTurn() {
    m_playerIntent = OUT_OF_WINDOW;
    useSoulCard = false;
}

PlayerTurn::~PlayerTurn() {
}

void PlayerTurn::init() {
    for (auto piece : ChessBoard->getChessList()) {
        piece->endTurn();
    }
    ChessBoard->getPlayer()->getGun()->reset();
    isPerforming = false;
    useSoulCard = false;
    m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
    m_moveList = MoveGen->getKingMove(m_PlayerPosition);
}

void PlayerTurn::update(float deltaTime) {
    if (isPerforming == false) {
        handlePlayerEvent();
    } else {
        // check if the player's turn is finished
        if (isEndPlayerTurn()) {
            //if WhiteKing is dead, change to WIN_TURN
            if (handleKillPiece()) {
                GTM->changeTurn(TURN::WIN_TURN);
                return;
            }
            //if player makes a mistake
            if (handleCheckKing()) {
                GTM->changeTurn(TURN::LOSE_TURN);
                return;
            }

            bool isBotTurn = false;
            for (auto piece : ChessBoard->getChessList()) {
                if (piece->getType() != PIECETYPE::PLAYER) {
                    piece->countTurnLeft();
                    if (piece->getTurnLeft() == 0) isBotTurn = true;
                }
            }
            //reload gun ammo
            if (m_playerIntent == WANT_TO_MOVE || useSoulCard) {
                if (ChessBoard->getPlayer()->getGun()->getCurrentAmmo() < ChessBoard->getPlayer()->getGun()->getMaxAmmo()
                    && ChessBoard->getPlayer()->getGun()->getCurrentCapacity() > 0) {
                    ChessBoard->getPlayer()->getGun()->addAmmo();
                } else {
                    ChessBoard->getPlayer()->getGun()->addCapacity();
                }
            }

            if (isBotTurn) GTM->changeTurn(TURN::BOT_TURN);
            else GTM->changeTurn(TURN::PLAYER_TURN);
        } else {
            // if the player shoots
            if (useSoulCard == false && m_playerIntent == MousePos::WANT_TO_SHOOT && ChessBoard->getPlayer()->getGun()->finishShoot() == false) {
                handleBulletHitbox();
            }
        }
    }
    for (auto piece : ChessBoard->getChessList()) {
        piece->update(deltaTime);
    }
}

void PlayerTurn::render() {
    if (ChessBoard->getChessList().size() == 1) {
        ChessBoard->getPlayer()->render();
        return;
    }
    int k = ChessBoard->getChessList().size();
    for (auto piece : ChessBoard->getChessList()) {
        if (piece != nullptr) piece->render();
    }
}

bool PlayerTurn::isEndPlayerTurn() {
    for (auto piece : ChessBoard->getChessList()) {
        if (piece->getType() != PIECETYPE::PLAYER) {
            if (piece->isEndTurn() == false) return false;
        }
    }
    if (ChessBoard->getPlayer()->isEndTurn() && ChessBoard->getPlayer()->getState() == IDLE) return true;
    return false;
}

MousePos PlayerTurn::getPlayerIntention() {
    for (auto pos : m_moveList) {
        if (ChessBoard->getChessBox(pos.x, pos.y)->isMouseHover()) {
            return MousePos::WANT_TO_MOVE;
        }
    }
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (ChessBoard->getChessBox(x, y)->isMouseHover()) {
                if (m_PlayerPosition.x == x && m_PlayerPosition.y == y) return MousePos::WANT_TO_MOVE;
                return MousePos::WANT_TO_SHOOT;
            }
        }
    }
    return MousePos::OUT_OF_BOARD;
}

void PlayerTurn::hideNearbyBox() {
    for (auto pos : m_moveList) {
        ChessBoard->getChessBox(pos.x, pos.y)->hideOutline();
    }
}

void PlayerTurn::handlePlayerEvent() {
    //using soul card
    if (ChessBoard->getPlayer()->getState() != STATE::IDLE) return;
    if (ChessBoard->getPlayer()->getGun()->finishShoot() == false) return;

    if (useSoulCard) {
        handleSoulCardEvent(ChessBoard->getSoulCard()->getPiece());
        return;

    }
    if (ChessBoard->getSoulCard()->isHover()) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ChessBoard->getSoulCard()->hasSoul()) {
            useSoulCard = true;
            return;
        }
    }
    //other event
    

    ChessBoard->getPlayer()->getGun()->setShootable(false);
    m_playerIntent = getPlayerIntention();
    switch (m_playerIntent) {
    case WANT_TO_MOVE:
        handleMoveEvent();
        break;
    case WANT_TO_SHOOT:
        hideNearbyBox();
        handleShootEvent();
        break;
    case OUT_OF_BOARD:
        hideNearbyBox();
        break;
    case OUT_OF_WINDOW:
        break;
    default:
        break;
    }
}

void PlayerTurn::handleMoveEvent() {
    for (auto pos : m_moveList) {
        if (ChessBoard->getChessBox(pos.x, pos.y)->isMouseHover()) {
            ChessBoard->getChessBox(pos.x, pos.y)->showOutline();
            if (ChessBoard->getChessBox(pos.x, pos.y)->isMouseClick()) {
                ChessBoard->getChessBox(pos.x, pos.y)->hideOutline();
                ChessBoard->getPlayer()->performTurn();
                ChessBoard->getPlayer()->setDestPosition(pos);
                ChessBoard->getPlayer()->changeState(STATE::MOVING);
                isPerforming = true;
                return;
            }
        } else {
            ChessBoard->getChessBox(pos.x, pos.y)->hideOutline();
        }
    }
}

void PlayerTurn::handleSoulCardEvent(PIECETYPE type) {
    switch (type) {
    case QUEEN:
        m_moveList = MoveGen->getQueenMove(m_PlayerPosition);
        break;
    case BISHOP:
        m_moveList = MoveGen->getBishopMove(m_PlayerPosition);
        break;
    case KNIGHT:
        m_moveList = MoveGen->getKnightMove(m_PlayerPosition);
        break;
    case ROOK:
        m_moveList = MoveGen->getRookMove(m_PlayerPosition);
        break;
    default:
        break;
    }
    bool moveSelected = false;
    for (auto pos : m_moveList) {
        ChessBoard->getChessBox(pos.x, pos.y)->showOutline();
        if (ChessBoard->getChessBox(pos.x, pos.y)->isMouseClick()) {
            ChessBoard->getPlayer()->performTurn();
            ChessBoard->getPlayer()->setDestPosition({ pos.x, pos.y });
            ChessBoard->getPlayer()->changeState(STATE::MOVING);
            isPerforming = true;
            moveSelected = true;
            break;
        }
    }
    if (moveSelected) {
        for (auto pos : m_moveList) {
            ChessBoard->getSoulCard()->reset();
            ChessBoard->getChessBox(pos.x, pos.y)->hideOutline();
        }
    }
}

void PlayerTurn::handleShootEvent() {
    ChessBoard->getPlayer()->getGun()->setShootable(true);
    if (ChessBoard->getPlayer()->getGun()->getCurrentAmmo() == 0) return; //no more shooting
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        ChessBoard->getPlayer()->getGun()->shoot();
        ChessBoard->getPlayer()->performTurn();
        isPerforming = true;
    }
}

void PlayerTurn::handleBulletHitbox() {
    for (auto bullet : ChessBoard->getPlayer()->getGun()->getBullets()) {
        for (auto piece : ChessBoard->getChessList()) {
            if (piece->getType() != PIECETYPE::PLAYER
                && piece->getGlobalBounds().contains(bullet->getHitbox())
                && bullet->isFlying()) {
                bullet->stop();
                if (piece->getState() == STATE::HURT || piece->getState() == STATE::KILL || piece->getState() == STATE::DEAD) continue;

                piece->setShootPosition(ChessBoard->getPlayer()->getCurrentPosition());
                if (bullet->getDamage() >= piece->getHealth()) {
                    piece->changeState(STATE::KILL);
                    if (piece->getType() != PIECETYPE::PAWN && piece->getType() != PIECETYPE::KING) {
                        ChessBoard->getSoulCard()->setPiece(piece->getType());
                    }
                } else {
                    piece->takeDamage(bullet->getDamage());
                    piece->changeState(STATE::HURT);
                }

                piece->performTurn();
            }
        }
    }
}

bool PlayerTurn::handleKillPiece() {
    int deadCount = 0;
    bool isWKingDead = false;
    for (int i = 0; i < ChessBoard->getChessList().size(); i++) {
        if (ChessBoard->getChessList()[i]->getState() == STATE::DEAD) {
            CCounter->addAmount(GameRule->getPriceChess(ChessBoard->getChessList()[i]->getType()));
            if (ChessBoard->getChessList()[i]->getType() == PIECETYPE::KING) {
                isWKingDead = true;
            }
            delete ChessBoard->getChessList()[i];
            ChessBoard->getChessList().erase(ChessBoard->getChessList().begin() + i);
            i--;
            deadCount++;
        }
    }
    return isWKingDead;
}

bool PlayerTurn::handleCheckKing() {
    m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
    for (auto piece : ChessBoard->getChessList()) {
        if (piece->getType() != PIECETYPE::PLAYER) {
            ChessPosition pos = piece->getCurrentPosition();
            pos = MoveGen->getNextMove(piece);
            //if piece kill player
            if (pos == m_PlayerPosition) {
                piece->setTurnLeft(0);
                piece->setDestPosition(m_PlayerPosition);
                piece->changeState(STATE::MOVING);
                piece->performTurn();
                return true;
            }
        }
    }
    return false;
}
