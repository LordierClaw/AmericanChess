#pragma once
#include "../GameStateBase.h"
#include "../../GameObject/GameButton.h"
#include "../../GameObject/ChessObject/Player.h"
#include "../../GameObject/ChessObject/Shotgun.h"
#include "../../GameObject/SoundButton.h"
#include "../../GameObject/GameRuleManager.h"
#include "../../GameConfig.h"

class GSModeSelect : public GameStateBase {
public:
	GSModeSelect();
	virtual ~GSModeSelect();

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
	sf::Sprite m_logo;
	sf::RectangleShape* m_blackScreen;
	bool isPerformTransition;

	Player* m_player;
};