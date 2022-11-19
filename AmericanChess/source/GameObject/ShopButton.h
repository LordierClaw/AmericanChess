#pragma once
#include "../GameObject/ChessObject/CashCounter.h"

class ShopButton {
public:
	ShopButton();
	~ShopButton();

	void init(std::string name);
	void init(std::string name, int price);
	void update(float deltaTime);
	void render();

	void setValue(int(*Func)());
	void setPrice(int price);
	void setPosition(sf::Vector2f pos);

	void setOnClick(void(*Func)());
private:
	float m_currentTime;

	bool m_isHandling;
	bool m_isHover;
	bool m_payable;

	std::string m_name;
	int (*m_btnGetValue)();

	sf::Text m_lblTitle;
	sf::Text m_lblPrice;
	sf::RectangleShape m_selected;
	int m_price;

	void (*m_btnClickFunc)();
};