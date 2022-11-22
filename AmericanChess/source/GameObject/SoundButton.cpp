#include "SoundButton.h"

SoundButton::SoundButton() {
	m_isHandling = false;
	m_currentTime = 0;
}

SoundButton::~SoundButton() {
}

void SoundButton::init() {
	DATA->addTexture("gui/btnSound_enable");
	DATA->addTexture("gui/btnSound_disable");
	this->setTexture(DATA->getTexture("gui/btnSound_enable"));
	this->setSize(sf::Vector2f(15.f*3, 13.f*3));
	this->setPosition(sf::Vector2f(10.f, 10.f));
	m_isHandling = false;
	m_currentTime = 0;

	m_sound = true;
}

void SoundButton::update(float deltaTime) {
	if (m_sound != DATA->isSoundEnable()) {
		if (DATA->isSoundEnable()) this->setTexture(DATA->getTexture("gui/btnSound_enable"));
		else this->setTexture(DATA->getTexture("gui/btnSound_disable"));
		m_sound = DATA->isSoundEnable();
	}

	if (m_isHandling == true) {
		m_currentTime += deltaTime;
		if (m_currentTime > 0.25f) {
			m_currentTime = 0;
			m_isHandling = false;
		} else return;
	}

	if (this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow()))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (DATA->isSoundEnable()) DATA->disableSound();
			else DATA->enableSound();
			m_isHandling = true;
		} else m_isHandling = false;
	}
}

void SoundButton::render() {
	WConnect->getWindow()->draw(*this);
}
