#include "GSPlay.h"

GSPlay::GSPlay() {
	isPerformTransition = false;
	m_currentTime = 0;
	m_overlayScreen = nullptr;
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
	m_soundBtn.init();

	if (Board::HasInstance() == false) ChessBoard->init();
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
			color.a = (int)(255 * (1 - (m_currentTime / TRANSITION_DURATION)));
			m_overlayScreen->setColor(color);
		} else {
			isPerformTransition = false;
			m_overlayScreen->setColor(sf::Color::Transparent);
			m_currentTime = 0;
			delete m_overlayScreen;
		}
	}
	// normal update
	m_soundBtn.update(deltaTime);
	ChessBoard->update(deltaTime);
}

void GSPlay::render() {
	WConnect->getWindow()->draw(m_background);
	m_soundBtn.render();
	ChessBoard->render();
	//transition
	if (isPerformTransition) WConnect->getWindow()->draw(*m_overlayScreen);
}