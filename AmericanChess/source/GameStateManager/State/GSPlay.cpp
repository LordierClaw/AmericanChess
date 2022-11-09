#include "GSPlay.h"

GSPlay::GSPlay() {
}

GSPlay::~GSPlay() {
}

void GSPlay::exit() {
}

void GSPlay::pause() {
}

void GSPlay::resume() {
}

void GSPlay::init() {
	GameButton* btn;
	btn = new GameButton("btnMenu", sf::Vector2f(30.f, 18.f));
	btn->setScale(sf::Vector2f(4.f, 4.f));
	btn->setPosition(sf::Vector2f(640.f, 40.f));
	btn->init();
	btn->setOnClick([]() {WConnect->getWindow()->close(); });
	m_btnList.push_back(btn);

	ChessBoard->init();

	m_blackScreen = new sf::RectangleShape(sf::Vector2f(SCREEN_WITDH, SCREEN_HEIGHT));
	m_blackScreen->setTexture(DATA->getTexture("bg"));
	isPerformTransition = true;
	m_currentTime = 0;

	m_background.setTexture(*DATA->getTexture("bg"));
	sf::Color bgColor = m_background.getColor();
	bgColor.a = 85;
	m_background.setColor(bgColor);
}

void GSPlay::update(float deltaTime) {
	//transition
	if (isPerformTransition == true) {
		m_currentTime += deltaTime;
		if (m_currentTime < TRANSITION_DURATION) {
			sf::Color color = m_blackScreen->getFillColor();
			color.a = 255 * (1-(m_currentTime/TRANSITION_DURATION));
			m_blackScreen->setFillColor(color);
		} else {
			isPerformTransition = false;
			m_blackScreen->setFillColor(sf::Color::Transparent);
			m_currentTime = 0;
			delete m_blackScreen;
		}
	}
	// normal update
	for (auto &btn : m_btnList) {
		btn->update(deltaTime);
	}
	ChessBoard->update(deltaTime);
}

void GSPlay::render() {
	WConnect->getWindow()->draw(m_background);
	for (auto &btn : m_btnList) {
		btn->render();
	}
	ChessBoard->render();

	//transition
	if (isPerformTransition) WConnect->getWindow()->draw(*m_blackScreen);
}