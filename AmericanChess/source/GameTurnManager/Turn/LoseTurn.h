#pragma once
#include "../GameTurnBase.h"
#include "../../GameStateManager/GameStateMachine.h"
#include "../../GameObject/GameButton.h"

class LoseTurn : public GameTurnBase {
public:
	LoseTurn();
	~LoseTurn();

	void init();
	void update(float deltaTime);
	void render();
private:
	ChessPiece* m_piece;
	void handleKillEvent(float deltaTime);
	void handleAfterDeath(float deltaTime);

	float m_currentTime;
	sf::RectangleShape* m_background;
	int m_alphaColor;
	GameButton* m_btnBack;

	void updateColor();
};