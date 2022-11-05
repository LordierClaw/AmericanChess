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
        if (ChessBoard->getPlayer()->isEndTurn() && ChessBoard->getPlayer()->getState() == IDLE) {
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
        }
    }
    for (auto piece : ChessBoard->getChessList()) {
        piece->update(deltaTime);
    }
}

void PlayerTurn::render() {
    for (auto piece : ChessBoard->getChessList()) {
        piece->render();
    }
}

//this is used to check ChessBox around Player
int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

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
    MousePos playerIntent = getPlayerIntention();
    switch (playerIntent) {
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