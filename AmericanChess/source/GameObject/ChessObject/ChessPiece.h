#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "../../Misc/GameMath.h"
#include "../../GameConfig.h"
#include "ChessPosition.h"

enum STATE {
	SHOWUP = 0,
	IDLE,
	READY_TO_MOVE,
	MOVING,
	HURT,
	KILL,
	DEAD
};

enum PIECETYPE {
	PLAYER = 0,
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN
};

class ChessPiece : public sf::Sprite {
public:
	ChessPiece();
	ChessPiece(std::string name);
	~ChessPiece();
	virtual void init(ChessPosition pos);
	virtual void update(float deltaTime);
	virtual void render();

	STATE getState();
	void changeState(STATE state);

	void setTurnLeft(int turnLeft);
	void countTurnLeft();
	int getTurnLeft();
	
	void setHealth(int health);
	int getHealth();

	PIECETYPE getType();

	//DO NOT USE setPosition()
	void setCurrentPosition(ChessPosition pos);
	ChessPosition getCurrentPosition();
	void setShootPosition(ChessPosition pos);
	void setDestPosition(ChessPosition pos);

	void performTurn();
	void endTurn();
	bool isEndTurn();

	bool m_isEndTurn;
private:
	std::string m_name;
	STATE m_state;
	int m_turnLeft;
	int m_health;
	PIECETYPE m_type;

	ChessPosition m_currentPos, m_destPos, m_shootPos;
	sf::Color m_color;
	ChessPosition m_chessPos;

	float m_currentTime;

	void handleShowUp(float deltaTime);
	void handleReady(float deltaTime);
	void handleMove(float deltaTime);
	void handleHurt(float deltaTime);
	void handleKill(float deltaTime);
};


