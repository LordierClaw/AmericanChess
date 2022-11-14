#include "Player.h"
#include "Shotgun.h"

Player::Player() : ChessPiece("B_King") {
	m_gun = nullptr;
}

Player::~Player() {
	if (m_gun != nullptr) delete m_gun;
}

void Player::init(ChessPosition pos) {
	ChessPiece::init(pos);
	m_gun = new Shotgun(this);
	m_gun->init();
}

void Player::update(float deltaTime) {
	ChessPiece::update(deltaTime);
	m_gun->update(deltaTime);
}

void Player::render() {
	ChessPiece::render();
	m_gun->render();
}

Shotgun* Player::getGun() {
	return m_gun;
}
