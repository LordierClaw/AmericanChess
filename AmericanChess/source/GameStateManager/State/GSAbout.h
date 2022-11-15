#pragma once
#include "../GameStateBase.h"
#include "../../GameObject/GameButton.h"
#include "../../GameConfig.h"

class GSAbout : public GameStateBase {
public:
	GSAbout();
	virtual ~GSAbout();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();
private:
	//sf::Sprite m_background;
	sf::Sprite* m_background;
	int m_alphaColor;
	GameButton* m_btnBack;
	float m_currentTime;

	void updateColor();
};