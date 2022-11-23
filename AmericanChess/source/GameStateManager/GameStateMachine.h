#pragma once
#include "../GameManager/Singleton.h"
#include <list>

#define GSM GameStateMachine::GetInstance()

class GameStateBase;

enum StateTypes {
	INVALID = 0,
	INTRO,
	MENU,
	ABOUT,
	PLAY,
	MODESELECT,
	UPGRADE,
	END
};

class GameStateMachine : public Singleton<GameStateMachine> {
public:
	GameStateMachine();
	~GameStateMachine();

	void changeState(GameStateBase* state);
	void changeState(StateTypes state);
	void pushState(StateTypes state);
	void popState();

	void performSateChange();

	GameStateBase* currentState() const;
	GameStateBase* nextState() const;
	bool needToChangeState();
	bool hasState();

private:
	std::list<GameStateBase*> m_StateStack;
	GameStateBase* m_ActiveState;
	GameStateBase* m_NextState;
};