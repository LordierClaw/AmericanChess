#include "Board.h"

Board::Board() {
    m_player = nullptr;
}

Board::~Board() {
    for (auto piece : m_ChessList) {
        if (piece != nullptr) delete piece;
    }
}

void Board::init() {
    DATA->addTexture("chess/Board");
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
    //
    m_player = new Player();
    m_player->init({0, 0});

    m_king = new ChessPiece("W_King");
    m_king->init();
    m_king->setCurrentPosition({ 6, 6 });
    //W_King->changeState(STATE::READY_TO_MOVE);
    m_king->setTurnLeft(3);

    ChessPiece* m_pawn = new ChessPiece("W_Pawn");
    m_pawn->init();
    m_pawn->setCurrentPosition({ 6, 2 });
    m_pawn->setTurnLeft(1);
    
    m_ChessList.push_back(m_king);
    m_ChessList.push_back(m_player);
    m_ChessList.push_back(m_pawn);

    GTM->changeTurn(TURN::PLAYER_TURN);
}

void Board::update(float deltaTime) {
    if (GTM->needToChangeTurn()) GTM->performTurnChange();
    GTM->currentTurn()->update(deltaTime);
}

void Board::render() {
    sort(m_ChessList.begin(), m_ChessList.end(), [](ChessPiece* a, ChessPiece* b) {
        return a->getCurrentPosition() < b->getCurrentPosition();
    });

    //draw the board itself
    WConnect->getWindow()->draw(*this);
    GTM->currentTurn()->render();

    //draw chessbox
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            m_ChessTable[y][x].render();
        }
    }
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