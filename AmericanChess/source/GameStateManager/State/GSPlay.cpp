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
	/*
	DATA->addTexture("chess/Board");
	//
	DATA->addTexture("chess/piece/B_Bishop");
	DATA->addTexture("chess/piece/B_King");
	DATA->addTexture("chess/piece/B_Knight");
	DATA->addTexture("chess/piece/B_Pawn");
	DATA->addTexture("chess/piece/B_Queen");
	DATA->addTexture("chess/piece/B_Rook");
	//
	DATA->addTexture("chess/piece/W_Bishop");
	DATA->addTexture("chess/piece/W_King");
	DATA->addTexture("chess/piece/W_Knight");
	DATA->addTexture("chess/piece/W_Pawn");
	DATA->addTexture("chess/piece/W_Queen");
	DATA->addTexture("chess/piece/W_Rook");
	//
	DATA->addTexture("chess/gun/Shotgun");

	//TESTING

	board.setTexture(*DATA->getTexture("chess/Board"));
	board.setOrigin(sf::Vector2f(136.f / 2, 120.f / 2));
	board.setScale(sf::Vector2f(550.f / 136, 550.f / 120));
	board.setPosition(sf::Vector2f(640.f, 373.f));
	
	player.setTexture(*DATA->getTexture("chess/piece/B_King"));
	player.setOrigin(sf::Vector2f(10.f / 2, 23.f / 2));
	player.setScale(sf::Vector2f(3.f, 3.f));
	player.setPosition(sf::Vector2f(640.f, 373.f));

	*/
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
