#pragma once
#include "../GameStateBase.h"

class GSMenu : public GameStateBase {
public:
	GSMenu();
	virtual ~GSMenu();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
};