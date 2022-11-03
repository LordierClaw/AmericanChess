#pragma once
#include "../GameTurnBase.h"

class BotTurn : public GameTurnBase {
public:
	BotTurn();
	~BotTurn();

	void init();
	void update(float deltaTime);
	void render();

private:
	bool isEndBotTurn();
	void handleBotEvent();
};