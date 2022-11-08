#include "Board.h"
#include "InfoBox.h"

Board::Board() {
    m_player = nullptr;
    m_king = nullptr;
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
}

Board::~Board() {;
    for (auto piece : m_ChessList) {
        if (piece != nullptr) delete piece;
    }
}

void Board::init() {
    //
    m_player = new Player();
    m_player->init({4, 7});
    m_ChessList.push_back(m_player);
    m_king = new ChessPiece("W_King");
    m_king->init({ 3, 0 }, 8, 4, 4);
    m_ChessList.push_back(m_king);

    ChessPiece* m_pawn = new ChessPiece("W_Pawn");
    m_pawn->init({ 2, 1 }, 3, 5, 5);
    m_ChessList.push_back(m_pawn);

    m_pawn = new ChessPiece("W_Pawn");
    m_pawn->init({ 3, 1 }, 3, 3, 5);
    m_ChessList.push_back(m_pawn);
    
    m_pawn = new ChessPiece("W_Pawn");
    m_pawn->init({ 4, 1 }, 3, 4, 5);
    m_ChessList.push_back(m_pawn);

    m_pawn = new ChessPiece("W_Pawn");
    m_pawn->init({ 5, 1 }, 3, 4, 5);
    m_ChessList.push_back(m_pawn);
    ChessPiece* m_bishop = new ChessPiece("W_Bishop");
    m_bishop->init({ 2, 0 }, 4, 3, 3);
    m_ChessList.push_back(m_bishop);

    ChessPiece* m_rook = new ChessPiece("W_Rook");
    m_rook->init({ 4, 0 }, 5, 4, 4);
    m_ChessList.push_back(m_rook);

    ChessPiece* m_knight = new ChessPiece("W_Knight");
    m_knight->init({ 5, 0 }, 3, 1, 2);
    m_ChessList.push_back(m_knight);
    //
    m_soulCard = new SoulCard();
    m_soulCard->init();
    m_infoBox = new InfoBox();
    m_infoBox->init();
    GTM->changeTurn(TURN::SHOWUP_TURN);
}

void Board::update(float deltaTime) {
    if (GTM->needToChangeTurn()) GTM->performTurnChange();
    GTM->currentTurn()->update(deltaTime);

    m_soulCard->update(deltaTime);
    m_infoBox->update(deltaTime);
}

void Board::render() {
    sort(m_ChessList.begin(), m_ChessList.end(), [](ChessPiece* a, ChessPiece* b) {
        return a->getCurrentPosition() < b->getCurrentPosition();
    });

    //draw the board itself
    WConnect->getWindow()->draw(*this);
    GTM->currentTurn()->render();
    m_soulCard->render();
    m_infoBox->render();

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

SoulCard* Board::getSoulCard() {
    return m_soulCard;
}