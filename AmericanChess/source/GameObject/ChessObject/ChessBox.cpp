#include "ChessBox.h"

ChessBox::ChessBox() {
}

//outline is disabled by default
ChessBox::ChessBox(sf::Vector2f size, ChessPosition pos) : sf::RectangleShape(size) {
	m_chessPos = pos;
	this->setOrigin(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2 - 23.f / 2 - 5.f));
	this->setPosition(m_chessPos.toPosition());
	this->setOutlineThickness(CHESSBOX_OUTLINE_THICKNESS);
	this->setOutlineColor(sf::Color::Transparent);
	this->setFillColor(sf::Color::Transparent);
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
	WConnect->getWindow()->draw(*this);
}

void ChessBox::showOutline() {
	this->setOutlineColor(CHESSBOX_OUTLINE_COLOR);
}

void ChessBox::hideOutline() {
	this->setOutlineColor(sf::Color::Transparent);
}