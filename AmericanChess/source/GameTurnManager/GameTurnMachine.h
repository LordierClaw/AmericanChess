#pragma once
#include "../GameManager/Singleton.h"
#include <list>

#define GTM GameTurnMachine::GetInstance()

class GameTurnBase;

enum TURN {
	SHOWUP = 0,
	PLAYER_TURN,
	BOT_TURN,
	END_BOARD
};

class GameTurnMachine : public Singleton<GameTurnMachine> {
public:
	GameTurnMachine();
	~GameTurnMachine();

	void changeTurn(GameTurnBase* turn);
	void changeTurn(TURN turn);

	void performTurnChange();

	GameTurnBase* currentTurn() const;
	GameTurnBase* nextTurn() const;
	bool needToChangeTurn();

	static int TURNCOUNT;
private:
	GameTurnBase* m_CurrentTurn;
	GameTurnBase* m_NextTurn;
};