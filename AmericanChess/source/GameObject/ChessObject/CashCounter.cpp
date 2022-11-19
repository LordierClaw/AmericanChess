#include "CashCounter.h"

CashCounter::CashCounter() {
	m_currentCash = m_newCash = 0;
	m_amountPerTime = 0;
}

CashCounter::~CashCounter() {
}

void CashCounter::init() {
	m_boxCash.setTexture(*DATA->getTexture("chess/CashCounter"));
	m_boxCash.setScale(sf::Vector2f(3.f, 3.f));
	m_boxCash.setPosition(sf::Vector2f(722.f, 28.f));

	m_lblCash.setFont(*DATA->getFont("Silver"));
	m_lblCash.setCharacterSize(32);
	m_lblCash.setStyle(sf::Text::Bold);
	m_lblCash.setPosition(sf::Vector2f(890.f, 27.f));
	m_lblCash.setFillColor(sf::Color(56, 52, 80));
	updateText();
}

void CashCounter::update(float deltaTime) {
	if (m_currentCash != m_newCash) {
		if (abs(m_amountPerTime) > abs(m_newCash - m_currentCash)) {
			m_amountPerTime = m_newCash - m_currentCash;
		}
		m_currentCash += m_amountPerTime;
		updateText();
	}
}

void CashCounter::render() {
	WConnect->getWindow()->draw(m_boxCash);
	WConnect->getWindow()->draw(m_lblCash);
}

void CashCounter::addAmount(int amount) {
	m_newCash += amount;
	if (m_newCash > 999999999) m_newCash = 999999999;
	if (m_newCash < 0) m_newCash = 0;
	m_amountPerTime = (m_newCash - m_currentCash) / 32;
	if (m_amountPerTime == 0) {
		if (m_newCash > m_currentCash) m_amountPerTime = 1;
		else if (m_newCash < m_currentCash) m_amountPerTime = -1;
	}
}

int CashCounter::getCurrentCash() {
	return m_currentCash;
}

void CashCounter::reset() {
	m_currentCash = m_newCash = 0;
	m_amountPerTime = 0;
	updateText();
}

void CashCounter::updateText() {
	m_lblCash.setString(std::to_string(m_currentCash));
	m_lblCash.setOrigin(sf::Vector2f(m_lblCash.getGlobalBounds().width, 0));
}
