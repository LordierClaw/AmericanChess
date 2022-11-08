#pragma once
#include "../GameObject/ChessObject/Board.h"
#include "../GameManager/Singleton.h"
#include "GameMath.h"

#define MoveGen ChessMoveGenerator::GetInstance()

class ChessMoveGenerator : public Singleton<ChessMoveGenerator> {
public:
	ChessPosition getNextMove(ChessPiece* piece);

private:
	ChessPosition m_PlayerPosition;

	bool positionCompare(ChessPosition a, ChessPosition b);
	bool validMove(ChessPosition pos);

	ChessPosition getKingMove(ChessPosition pos);
	ChessPosition getQueenMove(ChessPosition pos);
	ChessPosition getBishopMove(ChessPosition pos);
	ChessPosition getRookMove(ChessPosition pos);
	ChessPosition getKnightMove(ChessPosition pos);
	ChessPosition getPawnMove(ChessPosition pos);
};