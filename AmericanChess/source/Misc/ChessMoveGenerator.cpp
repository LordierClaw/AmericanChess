#include "ChessMoveGenerator.h"

ChessPosition ChessMoveGenerator::getNextMove(ChessPiece* piece) {
    m_PlayerPosition = ChessBoard->getPlayer()->getCurrentPosition();
    PIECETYPE type = piece->getType();
    ChessPosition pos;
    switch (type) {
    case KING:
        pos = getKingMove(piece->getCurrentPosition());
        break;
    case QUEEN:
        pos = getQueenMove(piece->getCurrentPosition());
        break;
    case BISHOP:
        pos = getBishopMove(piece->getCurrentPosition());
        break;
    case KNIGHT:
        pos = getKnightMove(piece->getCurrentPosition());
        break;
    case ROOK:
        pos = getRookMove(piece->getCurrentPosition());
        break;
    case PAWN:
        pos = getPawnMove(piece->getCurrentPosition());
        break;
    default:
        break;
    }
    return pos;
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
            if (pos == piece->getCurrentPosition()) return false;
        }
    }
    return true;
}

ChessPosition ChessMoveGenerator::getKingMove(ChessPosition pos) {
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    ChessPosition nextPos = pos;
    for (int i = 0; i < 8; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x = pos.x + dx[i];
        tmpPos.y = pos.y + dy[i];
        if (validMove(tmpPos) == false) continue;
        if (tmpPos == m_PlayerPosition) return tmpPos; //kill player immediately

        if (nextPos == pos) {
            nextPos = tmpPos;
            continue;
        }

        if (positionCompare(tmpPos, nextPos)) nextPos = tmpPos;
    }

    return nextPos;
}

ChessPosition ChessMoveGenerator::getQueenMove(ChessPosition pos) {
    ChessPosition pos1 = getRookMove(pos);
    ChessPosition pos2 = getBishopMove(pos);
    ChessPosition nextPos = pos;
    if (positionCompare(pos1, nextPos)) nextPos = pos1;
    if (positionCompare(pos2, nextPos)) nextPos = pos2;
    return nextPos;
}

ChessPosition ChessMoveGenerator::getBishopMove(ChessPosition pos) {
    ChessPosition nextPos = pos;

    for (int i = -7; i <= 7; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x += i;
        tmpPos.y += i;
        if (tmpPos == pos) continue;
        if (validMove(tmpPos) == false) continue;
        if (tmpPos == m_PlayerPosition) return tmpPos; //kill player immediately

        if (nextPos == pos) {
            nextPos = tmpPos;
            continue;
        }

        if (positionCompare(tmpPos, nextPos)) nextPos = tmpPos;
    }

    for (int i = -7; i < 7; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x -= i;
        tmpPos.y += i;
        if (tmpPos == pos) continue;
        if (validMove(tmpPos) == false) continue;
        if (tmpPos == m_PlayerPosition) return tmpPos; //kill player immediately

        if (nextPos == pos) {
            nextPos = tmpPos;
            continue;
        }

        if (positionCompare(tmpPos, nextPos)) nextPos = tmpPos;
    }

    return nextPos;
}

ChessPosition ChessMoveGenerator::getRookMove(ChessPosition pos) {
    ChessPosition nextPos = pos;
    //horizontal move
    for (int i = 0; i < 8; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x = i;
        if (tmpPos == pos) continue;
        if (validMove(tmpPos) == false) continue;
        if (tmpPos == m_PlayerPosition) return tmpPos; //kill player immediately

        if (nextPos == pos) {
            nextPos = tmpPos;
            continue;
        }

        if (positionCompare(tmpPos, nextPos)) nextPos = tmpPos;
    }
    //vertical move
    for (int i = 0; i < 8; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.y = i;
        if (tmpPos == pos) continue;
        if (validMove(tmpPos) == false) continue;
        if (tmpPos == m_PlayerPosition) return tmpPos; //kill player immediately

        if (nextPos == pos) {
            nextPos = tmpPos;
            continue;
        }

        if (positionCompare(tmpPos, nextPos)) nextPos = tmpPos;
    }
    
    return nextPos;
}

ChessPosition ChessMoveGenerator::getKnightMove(ChessPosition pos) {
    int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

    ChessPosition nextPos = pos;
    for (int i = 0; i < 8; i++) {
        ChessPosition tmpPos = pos;
        tmpPos.x = pos.x + dx[i];
        tmpPos.y = pos.y + dy[i];
        if (validMove(tmpPos) == false) continue;
        if (tmpPos == m_PlayerPosition) return tmpPos; //kill player immediately

        if (nextPos == pos) {
            nextPos = tmpPos;
            continue;
        }

        if (positionCompare(tmpPos, nextPos)) nextPos = tmpPos;
    }

    return nextPos;
}

ChessPosition ChessMoveGenerator::getPawnMove(ChessPosition pos) {
    if (pos.y == 7) return pos;
    ChessPosition nextPos = pos;
    nextPos.y++;
    if (nextPos.y == m_PlayerPosition.y) {
        if (nextPos.x - 1 == m_PlayerPosition.x) nextPos.x--;
        else if (nextPos.x + 1 == m_PlayerPosition.x) nextPos.x++;
    }
    return nextPos;
}
