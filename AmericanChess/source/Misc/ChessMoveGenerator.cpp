#include "ChessMoveGenerator.h"

ChessMoveGenerator::ChessMoveGenerator() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_hasPiece[i][j] = 0;
        }
    }
}

ChessMoveGenerator::~ChessMoveGenerator() {
}

ChessPosition ChessMoveGenerator::getNextMove(ChessPiece* piece) {
    m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
    PIECETYPE type = piece->getType();
    std::vector<ChessPosition> moveList;
    switch (type) {
    case PAWN:
        return getPawnMove(piece->getCurrentPosition());
        break;
    case KING:
        moveList = getKingMove(piece->getCurrentPosition());
        break;
    case QUEEN:
        moveList = getQueenMove(piece->getCurrentPosition());
        break;
    case BISHOP:
        moveList = getBishopMove(piece->getCurrentPosition());
        break;
    case KNIGHT:
        moveList = getKnightMove(piece->getCurrentPosition());
        break;
    case ROOK:
        moveList = getRookMove(piece->getCurrentPosition());
        break;
    default:
        break;
    }

    ChessPosition nextPos = piece->getCurrentPosition();
    for (auto pos : moveList) {
        if (pos == m_PlayerPosition) return pos;
        if (validMove(pos) == false) continue;
        if (nextPos == piece->getCurrentPosition()) {
            nextPos = pos;
            continue;
        }
        if (positionCompare(pos, nextPos)) nextPos = pos;
    }

    return nextPos;
}

//return true if position A is better than B
bool ChessMoveGenerator::positionCompare(ChessPosition a, ChessPosition b) {
    float dA = GameMath::getDistance(a.toPosition(), m_PlayerPosition.toPosition());
    float dB = GameMath::getDistance(b.toPosition(), m_PlayerPosition.toPosition());
    return dA <= dB;
}

bool ChessMoveGenerator::validMove(ChessPosition pos) {
    if (pos.x < 0 || pos.y < 0 || pos.x > 7 || pos.y > 7) return false;

    for (auto piece : ChessBoard->getChessList()) {
        if (piece->getType() != PIECETYPE::PLAYER) {
            if (pos == piece->getCurrentPosition() || pos == piece->getDestPosition()) return false;
        }
    }
    return true;
}

std::vector<ChessPosition> ChessMoveGenerator::getKingMove(ChessPosition pos) {
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    std::vector<ChessPosition> moveList;
    ChessPosition nextPos = pos;
    for (int i = 0; i < 8; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x = pos.x + dx[i];
        tmpPos.y = pos.y + dy[i];
        if (validMove(tmpPos) == false) continue;
        moveList.push_back(tmpPos);
    }

    return moveList;
}

std::vector<ChessPosition> ChessMoveGenerator::getQueenMove(ChessPosition pos) {
    std::vector<ChessPosition> moveList = getRookMove(pos);
    std::vector<ChessPosition> bishopMove = getBishopMove(pos);
    for (auto pos : bishopMove) {
        moveList.push_back(pos);
    }
    return moveList;
}

std::vector<ChessPosition> ChessMoveGenerator::getBishopMove(ChessPosition pos) {
    std::vector<ChessPosition> moveList;

    for (int i = 1; pos.x + i <= 7 && pos.y + i <= 7; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x += i;
        tmpPos.y += i;
        if (validMove(tmpPos) == false) break; //the path is blocked
        moveList.push_back(tmpPos);
    }

    for (int i = 1; pos.x - i >= 0 && pos.y - i >= 0; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x -= i;
        tmpPos.y -= i;
        if (validMove(tmpPos) == false) break; //the path is blocked
        moveList.push_back(tmpPos);
    }

    for (int i = 1; pos.x + i <= 7 && pos.y - i >= 0; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x += i;
        tmpPos.y -= i;
        if (tmpPos == pos) continue;
        if (validMove(tmpPos) == false) break; //the path is blocked
        moveList.push_back(tmpPos);
    }

    for (int i = 1; pos.x - i >= 0 && pos.y + i <= 7; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x -= i;
        tmpPos.y += i;
        if (validMove(tmpPos) == false) break; //the path is blocked
        moveList.push_back(tmpPos);
    }

    return moveList;
}

std::vector<ChessPosition> ChessMoveGenerator::getRookMove(ChessPosition pos) {
    std::vector<ChessPosition> moveList;
    //move right
    for (int i = 1; pos.x + i <= 7; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x += i;
        if (validMove(tmpPos) == false) break; // the path is blocked
        moveList.push_back(tmpPos);
    }
    //move left
    for (int i = 1; pos.x - i >= 0; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x -= i;
        if (validMove(tmpPos) == false) break; // the path is blocked
        moveList.push_back(tmpPos);
    }
    //move up
    for (int i = 1; pos.y + i <= 7; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.y += i;
        if (validMove(tmpPos) == false) break; // the path is blocked
        moveList.push_back(tmpPos);
    }
    //move down
    for (int i = 1; pos.y - i >= 0; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.y -= i;
        if (validMove(tmpPos) == false) break; // the path is blocked
        moveList.push_back(tmpPos);
    }
    
    return moveList;
}

std::vector<ChessPosition> ChessMoveGenerator::getKnightMove(ChessPosition pos) {
    int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

    std::vector<ChessPosition> moveList;
    for (int i = 0; i < 8; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x = pos.x + dx[i];
        tmpPos.y = pos.y + dy[i];
        if (validMove(tmpPos) == false) continue;
        moveList.push_back(tmpPos);
    }

    return moveList;
}

ChessPosition ChessMoveGenerator::getPawnMove(ChessPosition pos) {
    if (pos.y == 7) return pos;
    ChessPosition nextPos = pos;
    nextPos.y++;
    if (nextPos.y == m_PlayerPosition.y) {
        if (nextPos.x == m_PlayerPosition.x) return pos;
        else if (nextPos.x - 1 == m_PlayerPosition.x) nextPos.x--;
        else if (nextPos.x + 1 == m_PlayerPosition.x) nextPos.x++;
    }
    if (validMove(nextPos)) return nextPos;
    else return pos;
}
