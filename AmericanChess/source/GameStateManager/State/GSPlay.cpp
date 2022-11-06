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
}

void GSPlay::update(float deltaTime) {
	for (auto &btn : m_btnList) {
		btn->update(deltaTime);
	}
	ChessBoard->update(deltaTime);
}

void GSPlay::render() {
	for (auto &btn : m_btnList) {
		btn->render();
	}
	ChessBoard->render();
}
