#pragma once
#include "../GameObject/ChessObject/Board.h"
#include "../GameManager/Singleton.h"
#include "GameMath.h"

#define MoveGen ChessMoveGenerator::GetInstance()

class ChessMoveGenerator : public Singleton<ChessMoveGenerator> {
public:
	ChessMoveGenerator();
	~ChessMoveGenerator();
	ChessPosition getNextMove(ChessPiece* piece);
private:
	ChessPosition m_PlayerPosition;

	bool m_hasPiece[8][8];

	bool positionCompare(ChessPosition a, ChessPosition b);
	bool validMove(ChessPosition pos);

public:
	std::vector<ChessPosition> getKingMove(ChessPosition pos);
	std::vector<ChessPosition> getQueenMove(ChessPosition pos);
	std::vector<ChessPosition> getBishopMove(ChessPosition pos);
	std::vector<ChessPosition> getRookMove(ChessPosition pos);
	std::vector<ChessPosition> getKnightMove(ChessPosition pos);
	ChessPosition getPawnMove(ChessPosition pos);
};