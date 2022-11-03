#pragma once
#include "ChessPiece.h"

class Shotgun;

class Player : public ChessPiece {
public:
	Player();
	~Player();
	void init(ChessPosition pos);
	void update(float deltaTime);
	void render();

	Shotgun* getGun();
private:
	Shotgun* m_gun;
};