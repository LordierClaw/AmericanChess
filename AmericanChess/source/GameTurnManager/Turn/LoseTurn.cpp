#include "LoseTurn.h"

LoseTurn::LoseTurn() {
}

LoseTurn::~LoseTurn() {
}

void LoseTurn::init() {
	ChessPosition playerPos = ChessBoard->getPlayer()->getCurrentPosition();
	for (auto piece : ChessBoard->getChessList()) {
		if (piece->getType() != PIECETYPE::PLAYER) {
			if (piece->getTurnLeft() == 0 && piece->getDestPosition() == playerPos) {
				m_piece = piece;
				continue;
			}
			piece->changeState(STATE::IDLE);
			piece->endTurn();
		}
	}

	m_btnBack = new GameButton("btnBackToMenu", sf::Vector2f(262.f, 64.f));
	m_btnBack->setPosition(sf::Vector2f(SCREEN_WITDH / 2, SCREEN_HEIGHT / 2 + 75.f));
	m_btnBack->setOnClick([]() {GSM->popState(); GSM->popState(); });
	m_btnBack->init();

	m_background = new sf::RectangleShape(sf::Vector2f(SCREEN_WITDH, SCREEN_HEIGHT));
	m_background->setTexture(DATA->getTexture("bg-dead"));
	m_alphaColor = 0;
	updateColor();

	isPerforming = true;
	m_currentTime = 0;

	GTM->resetCount();
}

void LoseTurn::update(float deltaTime) {
	if (isPerforming == true) handleKillEvent(deltaTime);
	else handleAfterDeath(deltaTime);
}

void LoseTurn::render() {
	for (auto piece : ChessBoard->getChessList()) {
		piece->render();
	}
	if (isPerforming == false) {
		WConnect->getWindow()->draw(*m_background);
		WConnect->getWindow()->draw(*m_btnBack);
	}
}

void LoseTurn::handleKillEvent(float deltaTime) {
	m_piece->update(deltaTime);
	ChessBoard->getPlayer()->update(deltaTime);
	if (ChessBoard->getPlayer()->getState() == STATE::IDLE && 
		m_piece->getGlobalBounds().intersects(ChessBoard->getPlayer()->getGlobalBounds())) {
		ChessBoard->getPlayer()->setShootPosition(m_piece->getCurrentPosition()); //player is killed
		ChessBoard->getPlayer()->changeState(STATE::KILL);
		ChessBoard->getPlayer()->performTurn();
	}
	if (ChessBoard->getPlayer()->getState() == STATE::DEAD && ChessBoard->getPlayer()->isEndTurn()) {
		isPerforming = false;
		ChessBoard->disableBoard();
		DATA->playSound("smb_gameover");
	}
}

void LoseTurn::handleAfterDeath(float deltaTime) {
	m_currentTime += deltaTime;
	if (m_currentTime < TRANSITION_DURATION*2) {
		m_alphaColor = std::min(255, (int)round(255 * m_currentTime / (TRANSITION_DURATION*2)));
	} else {
		m_alphaColor = 255;
		m_btnBack->update(deltaTime);
	}
	updateColor();
}

void LoseTurn::updateColor() {
	sf::Color color = m_background->getFillColor();
	color.a = m_alphaColor;
	m_background->setFillColor(color);

	color = m_btnBack->getFillColor();
	color.a = m_alphaColor;
	m_btnBack->setFillColor(color);
}
