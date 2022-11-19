#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "../../GameManager/Singleton.h"

#define CCounter CashCounter::GetInstance()

class CashCounter : public Singleton<CashCounter> {
public:
	CashCounter();
	~CashCounter();

	void init();
	void update(float deltaTime);
	void render();

	void addAmount(int amount);
	int getCurrentCash();

	void reset();
private:
	void updateText();

	sf::Text m_lblCash;
	sf::Sprite m_boxCash;
	int m_currentCash;
	int m_newCash;
	int m_amountPerTime;
};