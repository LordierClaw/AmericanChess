#pragma once
#include "../GameStateBase.h"
#include "../../GameConfig.h"
#include "../../GameObject/GameButton.h"
#include "../../GameObject/ChessObject/Board.h"
#include "../../GameObject/ShopButton.h"

class GSUpgrade : public GameStateBase {
public:
	GSUpgrade();
	virtual ~GSUpgrade();

	void exit();
	void pause();
	void resume();

	void init();
	void update(float deltaTime);
	void render();

private:
	sf::Sprite* m_background;
	sf::Text m_title;
	GameButton* m_btnContinue;

	sf::Sprite m_shopBoard;
	std::vector<ShopButton*> m_shopBtnList;

	int m_alphaColor;
	float m_currentTime;

	void updateColor();
	void handleUpgrade(float deltaTime);
};