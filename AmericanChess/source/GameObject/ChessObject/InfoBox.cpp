#include "InfoBox.h"

InfoBox::InfoBox() {
}

InfoBox::~InfoBox() {
}

void InfoBox::init() {
	m_heathLbl.setFont(*DATA->getFont("Silver"));
	m_turnLbl.setFont(*DATA->getFont("Silver"));
	m_heathLbl.setCharacterSize(36);
	m_turnLbl.setCharacterSize(36);

	m_heathLbl.setPosition(sf::Vector2f(245.f, 300.f));
	m_turnLbl.setPosition(sf::Vector2f(245.f, 350.f));

	m_gunInfoList.resize(6, sf::Text("", *DATA->getFont("Silver"), 36));
	m_gunInfoList[0].setString("RANGE");
	m_gunInfoList[2].setString("DAMAGE");
	m_gunInfoList[4].setString("PELLET");
	for (int i = 0; i < 6; i++) {
		float offset = 40.f * i;
		if (i % 2 != 0) offset -= 7;
		else {
			m_gunInfoList[i].setStyle(sf::Text::Underlined | sf::Text::Bold);
		}
		m_gunInfoList[i].setPosition(sf::Vector2f(300.f, 250.f + offset));
	}
	m_isDisplay = false;
}

void InfoBox::update(float deltaTime) {
	for (auto piece : ChessBoard->getChessList()) {
		if (piece->getType() != PIECETYPE::PLAYER
			&& (piece->getState() == STATE::IDLE || piece->getState() == STATE::READY_TO_MOVE)
			&& piece->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow()))
		) {
			display(piece);
			return;
		}
	}
	m_isDisplay = false;

	m_gunInfoList[1].setString(std::to_string(GameRule->getShotgunRange()));
	m_gunInfoList[3].setString(std::to_string(std::max(GameRule->getShotgunDMG()-3, 1)) + "-" + std::to_string(GameRule->getShotgunDMG()));
	m_gunInfoList[5].setString(std::to_string(GameRule->getShotgunSpray()));
	for (auto &text : m_gunInfoList) {
		text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, 0));
	}
}

void InfoBox::render() {
	if (m_isDisplay) {
		WConnect->getWindow()->draw(m_heathLbl);
		WConnect->getWindow()->draw(m_turnLbl);
	} else {
		for (auto text : m_gunInfoList) {
			WConnect->getWindow()->draw(text);
		}
	}
}

void InfoBox::display(ChessPiece* piece) {
	m_isDisplay = true;
	//
	m_heathLbl.setString("Health: " + std::to_string(piece->getHealth()));
	m_turnLbl.setString("Turn: " + std::to_string(piece->getTurnLeft()) + "/" + std::to_string(piece->getQueueSize()));
}