#pragma once
#include "../GameManager/Singleton.h"
#include <list>

#define GTM GameTurnMachine::GetInstance()

class GameTurnBase;

enum TURN {
	SHOWUP_TURN = 0,
	PLAYER_TURN,
	BOT_TURN,
	WIN_TURN,
	LOSE_TURN
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

	int getTurnCount();

	void resetCount();
private:
	int m_TurnCount;
	GameTurnBase* m_CurrentTurn;
	GameTurnBase* m_NextTurn;
};