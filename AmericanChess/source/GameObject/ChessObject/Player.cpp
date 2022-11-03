#include "Player.h"
#include "Shotgun.h"

Player::Player() : ChessPiece("B_King") {
	m_gun = nullptr;
}

Player::~Player() {
}

void Player::init(ChessPosition pos) {
	ChessPiece::init();
	this->setCurrentPosition(pos);
	m_gun = new Shotgun(this);
	m_gun->init();
	m_gun->sync();
}

void Player::update(float deltaTime) {
	ChessPiece::update(deltaTime);
	m_gun->setPosition(this->getPosition());
	m_gun->update(deltaTime);
}

void Player::render() {
	ChessPiece::render();
	m_gun->render();
}

Shotgun* Player::getGun() {
	return m_gun;
}
