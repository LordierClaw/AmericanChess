#pragma once
#include "../GameStateBase.h"
#include "../../GameObject/GameButton.h"
#include "../../GameObject/ChessObject/Board.h"

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

	float m_currentTime;
	sf::Sprite m_background;
	sf::RectangleShape* m_blackScreen;
	bool isPerformTransition;
};