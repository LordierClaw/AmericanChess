#pragma once
#include "../GameStateBase.h"
#include "../../GameObject/GameButton.h"
#include "../../GameObject/ChessObject/Board.h"
#include "../../GameObject/SoundButton.h"

class GSPlay : public GameStateBase {
public:
	GSPlay();
	virtual ~GSPlay();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	std::list<GameButton*> m_btnList;
	SoundButton m_soundBtn;

	float m_currentTime;
	sf::Sprite m_background;
	sf::Sprite* m_overlayScreen;
	bool isPerformTransition;
};