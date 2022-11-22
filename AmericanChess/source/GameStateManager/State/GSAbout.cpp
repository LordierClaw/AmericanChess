#include "GSAbout.h"

GSAbout::GSAbout() {
}

GSAbout::~GSAbout() {
	if (m_btnBack != nullptr) delete m_btnBack;
	if (m_background != nullptr) delete m_background;
}

void GSAbout::exit() {
}

void GSAbout::pause() {
}

void GSAbout::resume() {
}

void GSAbout::init() {
	m_background = new sf::Sprite;
	m_background->setTexture(*DATA->getTexture("bg-about"));
	m_btnBack = new GameButton("btnBackToMenu", sf::Vector2f(262.f, 64.f));
	m_btnBack->setPosition(sf::Vector2f(SCREEN_WITDH / 2, SCREEN_HEIGHT / 2 + 250.f));
	m_btnBack->setOnClick([]() {GSM->popState(); });
	m_btnBack->init();
}

void GSAbout::update(float deltaTime) {
	m_currentTime += deltaTime;
	if (m_currentTime < TRANSITION_DURATION * 2) {
		m_alphaColor = std::min(255, (int)round(255 * m_currentTime / (TRANSITION_DURATION * 2)));
	} else {
		m_alphaColor = 255;
		m_btnBack->update(deltaTime);
	}
	updateColor();
}

void GSAbout::render() {
	WConnect->getWindow()->draw(*m_background);
	m_btnBack->render();
}

void GSAbout::updateColor() {
	sf::Color color = m_background->getColor();
	color.a = m_alphaColor;
	m_background->setColor(color);

	color = m_btnBack->getFillColor();
	color.a = m_alphaColor;
	m_btnBack->setFillColor(color);
}
