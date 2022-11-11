#include "ChessBox.h"

ChessBox::ChessBox() {
}

ChessBox::ChessBox(sf::Vector2f size, ChessPosition pos) : sf::RectangleShape(size) {
	m_chessPos = pos;
	this->setOrigin(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2 - 23.f / 2 - 5.f));
	this->setPosition(m_chessPos.toPosition());
	this->setFillColor(sf::Color::Transparent);
	m_outline.setTexture(*DATA->getTexture("chess/MoveBox"));
	m_outline.setOrigin(sf::Vector2f(45.f, 45.f));
	m_outline.setPosition(this->getPosition().x, this->getPosition().y + 23.f / 2 + 4.7);
	m_isVisible = false;
}

ChessBox::~ChessBox() {
}

bool ChessBox::isMouseHover() {
	if (this->getGlobalBounds().contains(
		(sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())
	)) return true;
	else return false;
}

bool ChessBox::isMouseClick() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isMouseHover()) return true;
	else return false;
}

ChessPosition ChessBox::getChessPosition() {
	return m_chessPos;
}

void ChessBox::render() {
	if (m_isVisible) WConnect->getWindow()->draw(m_outline);
}

void ChessBox::showOutline() {
	m_isVisible = true;
}

void ChessBox::hideOutline() {
	m_isVisible = false;
}