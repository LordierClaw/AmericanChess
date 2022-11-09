#pragma once
#include "../GameTurnBase.h"

class ShowupTurn : public GameTurnBase {
public:
	ShowupTurn();
	~ShowupTurn();

	void init();
	void update(float deltaTime);
	void render();

private:
	void handlePlayerShowUp(float deltaTime);
	void handleBotShowUp(float deltaTime);

	float m_currentTime;
};