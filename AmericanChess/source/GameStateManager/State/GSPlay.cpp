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
	ChessBoard->setLevel(1);

	isPerformTransition = true;
	m_currentTime = 0;

	m_background.setTexture(*DATA->getTexture("bg"));
	sf::Color bgColor = m_background.getColor();
	bgColor.a = 150;
	m_background.setColor(bgColor);

	m_overlayScreen = new sf::Sprite();
	m_overlayScreen->setTexture(*DATA->getTexture("bg"));
	m_overlayScreen->setColor(bgColor);
}

void GSPlay::update(float deltaTime) {
	//transition
	if (isPerformTransition == true) {
		m_currentTime += deltaTime;
		if (m_currentTime < TRANSITION_DURATION) {
			sf::Color color = m_overlayScreen->getColor();
			color.a = 255 * (1-(m_currentTime/TRANSITION_DURATION));
			m_overlayScreen->setColor(color);
		} else {
			isPerformTransition = false;
			m_overlayScreen->setColor(sf::Color::Transparent);
			m_currentTime = 0;
			delete m_overlayScreen;
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
	if (isPerformTransition) WConnect->getWindow()->draw(*m_overlayScreen);
}