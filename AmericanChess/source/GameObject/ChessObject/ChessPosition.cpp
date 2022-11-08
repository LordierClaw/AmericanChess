#include "ChessPosition.h"

ChessPosition::ChessPosition() {
    this->x = 0;
    this->y = 0;
}
ChessPosition::ChessPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

ChessPosition::~ChessPosition() {
}

sf::Vector2f ChessPosition::toPosition() {
    float boardX = 382.f, boardY = 120.f;
    float offsetX = x * 64.5 + 64.5 / 2, offsetY = y * 64.5 + 23.f / 2 + 5.f;
    return sf::Vector2f(boardX + offsetX, boardY + offsetY);
}

bool operator < (ChessPosition pos1, ChessPosition pos2) {
    if (pos1.y == pos2.y) return pos1.x < pos2.x;
    else return pos1.y < pos2.y;
}

bool operator > (ChessPosition pos1, ChessPosition pos2) {
    if (pos1.y == pos2.y) return pos1.x > pos2.x;
    else return pos1.y > pos2.y;
}

bool operator == (ChessPosition pos1, ChessPosition pos2) {
    return (pos1.x == pos2.x && pos1.y == pos2.y);
}

bool operator != (ChessPosition pos1, ChessPosition pos2) {
    return (pos1.x != pos2.x || pos1.y != pos2.y);
}