#include "SoulCard.h"

SoulCard::SoulCard() {
	DATA->addTexture("chess/card/B_Cardbox");
	m_hasSoul = false;
}

SoulCard::~SoulCard() {
}

void SoulCard::init() {
	this->setTexture(DATA->getTexture("chess/card/B_Cardbox"));
	this->setSize(sf::Vector2f(120.f, 120.f));
	this->setOrigin(sf::Vector2f(60.f, 60.f));
	this->setPosition(sf::Vector2f(1004.f, 373.f));

	m_piece.setScale(sf::Vector2f(3.f, 3.f));
	m_piece.setOrigin(sf::Vector2f(16.f / 2, 23.f / 2));
	m_piece.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - 10.f));
	m_hasSoul = false;
}

void SoulCard::update(float deltaTime) {
	if (m_hasSoul && isHover()) {
		handleClick();
	}
}

void SoulCard::render() {
	WConnect->getWindow()->draw(*this);
	if (m_hasSoul) WConnect->getWindow()->draw(m_piece);
}

void SoulCard::setPiece(PIECETYPE type) {
	if (m_hasSoul) return;

	m_type = type;
	std::string name;
	switch (type) {
	case QUEEN:
		name = "W_Queen";
		break;
	case BISHOP:
		name = "W_Bishop";
		break;
	case KNIGHT:
		name = "W_Knight";
		break;
	case ROOK:
		name = "W_Rook";
		break;
	default:
		break;
	}
	m_hasSoul = true;
	m_piece.setTexture(*DATA->getTexture("chess/piece/" + name));
}

PIECETYPE SoulCard::getPiece() {
	return m_type;
}

bool SoulCard::isHover() {
	if (this->getGlobalBounds().contains(
		(sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())
	)) return true;
	return false;
}

void SoulCard::handleClick() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		
	}
}
