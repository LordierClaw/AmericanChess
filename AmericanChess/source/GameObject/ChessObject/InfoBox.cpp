#include "InfoBox.h"

InfoBox::InfoBox() {
	DATA->addFont("Silver");
}

InfoBox::~InfoBox() {
}

void InfoBox::init() {
	m_heathLbl.setFont(*DATA->getFont("Silver"));
	m_turnLbl.setFont(*DATA->getFont("Silver"));
	m_heathLbl.setCharacterSize(36);
	m_turnLbl.setCharacterSize(36);

	m_heathLbl.setPosition(sf::Vector2f(200.f, 200.f));
	m_turnLbl.setPosition(sf::Vector2f(200.f, 250.f));

	m_isDisplay = false;
}

void InfoBox::update(float deltaTime) {
	for (auto piece : ChessBoard->getChessList()) {
		if (piece->getType() != PIECETYPE::PLAYER && piece->getGlobalBounds().contains(
			(sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())
		)) {
			display(piece);
			return;
		}
	}
	m_isDisplay = false;
}

void InfoBox::render() {
	if (m_isDisplay) {
		WConnect->getWindow()->draw(m_heathLbl);
		WConnect->getWindow()->draw(m_turnLbl);
	}
}

void InfoBox::display(ChessPiece* piece) {
	m_isDisplay = true;
	m_heathLbl.setString("Health: " + std::to_string(piece->getHealth()));
	m_turnLbl.setString("Turn: " + std::to_string(piece->getTurnLeft()) + "/" + std::to_string(piece->getQueueSize()));
}