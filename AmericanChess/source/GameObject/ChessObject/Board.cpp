#include "Board.h"
#include "InfoBox.h"

Board::Board() {
    m_player = nullptr;
    m_infoBox = nullptr;
    m_soulCard = nullptr;
    m_ammoBox = nullptr;
    m_isEnable = false;
}

Board::~Board() {;
}

void Board::init() {
    m_isEnable = true;
    //
    this->setTexture(DATA->getTexture("chess/Board"));
    this->setSize(sf::Vector2f(550.f, 550.f + 6.f)); //DO NOT change y value, because I want to stretch the texture
    this->setOrigin(sf::Vector2f(550.f / 2, 550.f / 2));
    this->setPosition(sf::Vector2f(640.f, 373.f));
    //generate a matrix of chessBox
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            m_ChessTable[y][x] = ChessBox(sf::Vector2f(64.5, 64.5), { x, y });
        }
    }
    if (CashCounter::HasInstance() == false) CCounter->init();
}

void Board::update(float deltaTime) {
    CCounter->update(deltaTime);
    if (GTM->needToChangeTurn()) GTM->performTurnChange();
    GTM->currentTurn()->update(deltaTime);

    if (m_isEnable == false) return;
    m_soulCard->update(deltaTime);
    m_infoBox->update(deltaTime);
    m_ammoBox->update(deltaTime);
}

void Board::render() {
    CCounter->render();
    sort(m_ChessList.begin(), m_ChessList.end(), [](ChessPiece* a, ChessPiece* b) {
        return a->getCurrentPosition() < b->getCurrentPosition();
    });

    //draw the board itself
    WConnect->getWindow()->draw(*this);
    GTM->currentTurn()->render();
    //
    if (m_isEnable == false) return;
    m_soulCard->render();
    m_infoBox->render();
    m_ammoBox->render();
    //draw chessbox
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            m_ChessTable[y][x].render();
        }
    }
}

void Board::setLevel(int level) {
    //clear board first
    for (auto piece : m_ChessList) {
        if (piece != nullptr) delete piece;
    }
    m_ChessList.clear();
    //
    m_ChessList = GameRule->getChessList(level);
    for (auto piece : m_ChessList) {
        if (piece->getType() == PLAYER) {
            m_player = (Player*)piece;
            break;
        }
    }
    //
    if (m_soulCard == nullptr) {
        m_soulCard = new SoulCard();
        m_soulCard->init();
    }
    if (m_infoBox == nullptr) {
        m_infoBox = new InfoBox();
        m_infoBox->init();
    }
    if (m_ammoBox == nullptr) {
        m_ammoBox = new GunAmmoBox();
        m_ammoBox->init();
    }
    if (level == 1) CCounter->reset();
    //
    m_soulCard->reset();
    m_ammoBox->setGun(m_player->getGun());
    GTM->changeTurn(TURN::SHOWUP_TURN);
}

Player* Board::getPlayer() {
    return m_player;
}

std::vector<ChessPiece*>& Board::getChessList() {
    return m_ChessList;
}

ChessBox* Board::getChessBox(int x, int y) {
    return &m_ChessTable[y][x];
}

SoulCard* Board::getSoulCard() {
    return m_soulCard;
}

void Board::disableBoard() {
    m_isEnable = false;
}

void Board::enableBoard() {
    m_isEnable = true;
}
