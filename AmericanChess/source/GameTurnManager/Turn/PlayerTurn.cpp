#include "PlayerTurn.h"

PlayerTurn::PlayerTurn() {
}

PlayerTurn::~PlayerTurn() {
}

void PlayerTurn::init() {
    std::cout << "Start of Player Turn" << '\n';
    for (auto piece : ChessBoard->getChessList()) {
        piece->endTurn();
    }
    ChessBoard->getPlayer()->getGun()->reset();
    isPerforming = false;
}

void PlayerTurn::update(float deltaTime) {
    m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
    if (isPerforming == false) {
        handlePlayerEvent();
    } else {
        // check if the player's turn is finished
        if (isEndPlayerTurn()) {
            //if WhiteKing is dead, change to END_TURN
            if (handleKillPiece()) {
                GTM->changeTurn(END_TURN);
                return;
            }

            bool isBotTurn = false;
            for (auto piece : ChessBoard->getChessList()) {
                if (piece->getType() != PIECETYPE::PLAYER) {
                    piece->countTurnLeft();
                    if (piece->getTurnLeft() == 0) isBotTurn = true;
                }
            }

            std::cout << "End of Player Turn" << '\n';
            if (isBotTurn) GTM->changeTurn(TURN::BOT_TURN);
            else GTM->changeTurn(TURN::PLAYER_TURN);
        } else {
            // if the player shoots
            if (m_playerIntent == MousePos::WANT_TO_SHOOT && ChessBoard->getPlayer()->getGun()->finishShoot() == false) {
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

//this is used to check ChessBox around Player
int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

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
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            bool isAiming = true;
            if (ChessBoard->getChessBox(x, y)->isMouseHover()) {
                for (int i = 0; i < 8; i++) {
                    int nx = m_PlayerPosition.x + dx[i];
                    int ny = m_PlayerPosition.y + dy[i];
                    if (nx == x && ny == y) {
                        isAiming = false;
                        break;
                    }
                }
                if (m_PlayerPosition.x == x && m_PlayerPosition.y == y) isAiming = false;
                if (isAiming) return MousePos::WANT_TO_SHOOT;
                else return MousePos::WANT_TO_MOVE;
            }
        }
    }
    return MousePos::OUT_OF_BOARD;
}

void PlayerTurn::hideNearbyBox() {
    for (int i = 0; i < 8; i++) {
        int nx = m_PlayerPosition.x + dx[i];
        int ny = m_PlayerPosition.y + dy[i];
        if (nx < 0 || nx > 7 || ny < 0 || ny > 7) continue;
        ChessBoard->getChessBox(nx, ny)->hideOutline();
    }
}

void PlayerTurn::handlePlayerEvent() {
    if (ChessBoard->getPlayer()->getState() != STATE::IDLE) return;
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
    for (int i = 0; i < 8; i++) {
        int nx = m_PlayerPosition.x + dx[i];
        int ny = m_PlayerPosition.y + dy[i];
        if (nx < 0 || nx > 7 || ny < 0 || ny > 7) continue;
        if (ChessBoard->getChessBox(nx, ny)->isMouseHover()) {
            ChessBoard->getChessBox(nx, ny)->showOutline();
            if (ChessBoard->getChessBox(nx, ny)->isMouseClick()) {
                ChessBoard->getChessBox(nx, ny)->hideOutline();
                ChessBoard->getPlayer()->performTurn();
                ChessBoard->getPlayer()->setDestPosition({ nx, ny });
                ChessBoard->getPlayer()->changeState(STATE::MOVING);
                isPerforming = true;
                return;
            }
        } else {
            ChessBoard->getChessBox(nx, ny)->hideOutline();
        }
    }
}

void PlayerTurn::handleShootEvent() {
    ChessBoard->getPlayer()->getGun()->setShootable(true);
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
                && piece->getState() != STATE::HURT
                && bullet->isFlying()) {
                bullet->stop();
                std::cout << "Piece located at " << piece->getCurrentPosition().x << " - " << piece->getCurrentPosition().y;
                std::cout << " is shot. Health: " << piece->getHealth() << "  Damage: " << bullet->getDamage() << '\n';
                piece->setShootPosition(ChessBoard->getPlayer()->getCurrentPosition());

                if (bullet->getDamage() >= piece->getHealth()) {
                    piece->changeState(STATE::KILL);
                    if (piece->getType() != PIECETYPE::PAWN && piece->getType() != PIECETYPE::KING) {
                        ChessBoard->getSoulCard()->setPiece(piece->getType());
                    }
                }
                else piece->changeState(STATE::HURT);

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
            if (ChessBoard->getChessList()[i]->getType() == PIECETYPE::KING) {
                std::cout << "WHITE KING IS DEAD!\n";
                isWKingDead = true;
            }
            delete ChessBoard->getChessList()[i];
            ChessBoard->getChessList().erase(ChessBoard->getChessList().begin() + i);
            i--;
            deadCount++;
        }
    }
    if (deadCount != 0) std::cout << "Dead Pieces: " << deadCount << '\n';
    return isWKingDead;
}

void setReadyState() {

}