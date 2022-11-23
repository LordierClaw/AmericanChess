#include "GameRuleManager.h"

GameRuleManager::GameRuleManager() {
	setMode(EASY);
}

GameRuleManager::~GameRuleManager() {
}

void GameRuleManager::setMode(GAMEMODE mode) {
	m_currentLevel = 0;
	switch (mode) {
	case EASY:
		//PLAYER GUN
		m_shotgunDamage = 5;
		m_shotgunRange = 350;
		m_shotgunSpray = 7;
		m_shotgunMaxAmmo = 2;
		m_shotgunMaxCapacity = 8;
		//CHESS PRICE
		m_priceList[PIECETYPE::KING] = 800;
		m_priceList[PIECETYPE::QUEEN] = 600;
		m_priceList[PIECETYPE::BISHOP] = 350;
		m_priceList[PIECETYPE::KNIGHT] = 350;
		m_priceList[PIECETYPE::ROOK] = 400;
		m_priceList[PIECETYPE::PAWN] = 250;
		//CHESS HEALTH
		m_healthList[PIECETYPE::KING] = 8;
		m_healthList[PIECETYPE::QUEEN] = 6;
		m_healthList[PIECETYPE::BISHOP] = 4;
		m_healthList[PIECETYPE::KNIGHT] = 3;
		m_healthList[PIECETYPE::ROOK] = 5;
		m_healthList[PIECETYPE::PAWN] = 3;
		//CHESS QUEUE SIZE
		m_queueSizeList[PIECETYPE::KING] = 4;
		m_queueSizeList[PIECETYPE::QUEEN] = 3;
		m_queueSizeList[PIECETYPE::BISHOP] = 3;
		m_queueSizeList[PIECETYPE::KNIGHT] = 2;
		m_queueSizeList[PIECETYPE::ROOK] = 4;
		m_queueSizeList[PIECETYPE::PAWN] = 5;
		break;
	case NORMAL:
		//PLAYER GUN
		m_shotgunDamage = 4;
		m_shotgunRange = 300;
		m_shotgunSpray = 6;
		m_shotgunMaxAmmo = 2;
		m_shotgunMaxCapacity = 6;
		//CHESS PRICE
		m_priceList[PIECETYPE::KING] = 1000;
		m_priceList[PIECETYPE::QUEEN] = 800;
		m_priceList[PIECETYPE::BISHOP] = 400;
		m_priceList[PIECETYPE::KNIGHT] = 400;
		m_priceList[PIECETYPE::ROOK] = 500;
		m_priceList[PIECETYPE::PAWN] = 300;
		//CHESS HEALTH
		m_healthList[PIECETYPE::KING] = 8;
		m_healthList[PIECETYPE::QUEEN] = 6;
		m_healthList[PIECETYPE::BISHOP] = 4;
		m_healthList[PIECETYPE::KNIGHT] = 3;
		m_healthList[PIECETYPE::ROOK] = 5;
		m_healthList[PIECETYPE::PAWN] = 3;
		//CHESS QUEUE SIZE
		m_queueSizeList[PIECETYPE::KING] = 4;
		m_queueSizeList[PIECETYPE::QUEEN] = 3;
		m_queueSizeList[PIECETYPE::BISHOP] = 3;
		m_queueSizeList[PIECETYPE::KNIGHT] = 2;
		m_queueSizeList[PIECETYPE::ROOK] = 4;
		m_queueSizeList[PIECETYPE::PAWN] = 5;
		break;
	case HARD:
		//PLAYER GUN
		m_shotgunDamage = 3;
		m_shotgunRange = 250;
		m_shotgunSpray = 6;
		m_shotgunMaxAmmo = 1;
		m_shotgunMaxCapacity = 5;
		//CHESS PRICE
		m_priceList[PIECETYPE::KING] = 1000;
		m_priceList[PIECETYPE::QUEEN] = 800;
		m_priceList[PIECETYPE::BISHOP] = 400;
		m_priceList[PIECETYPE::KNIGHT] = 400;
		m_priceList[PIECETYPE::ROOK] = 500;
		m_priceList[PIECETYPE::PAWN] = 300;
		//CHESS HEALTH
		m_healthList[PIECETYPE::KING] = 9;
		m_healthList[PIECETYPE::QUEEN] = 7;
		m_healthList[PIECETYPE::BISHOP] = 5;
		m_healthList[PIECETYPE::KNIGHT] = 4;
		m_healthList[PIECETYPE::ROOK] = 6;
		m_healthList[PIECETYPE::PAWN] = 4;
		//CHESS QUEUE SIZE
		m_queueSizeList[PIECETYPE::KING] = 4;
		m_queueSizeList[PIECETYPE::QUEEN] = 3;
		m_queueSizeList[PIECETYPE::BISHOP] = 3;
		m_queueSizeList[PIECETYPE::KNIGHT] = 2;
		m_queueSizeList[PIECETYPE::ROOK] = 4;
		m_queueSizeList[PIECETYPE::PAWN] = 5;
		break;
	default:
		break;
	}
}

void GameRuleManager::levelInit(int n) {
	//clear the existing chesslist
	m_ChessList.clear();
	switch (n) {
	case 1:
		level1();
		break;
	case 2:
		level2();
		break;
	case 3:
		level3();
		break;
	case 4:
		level4();
		break;
	case 5:
		level5();
		break;
	default:
		break;
	}
	m_currentLevel = n;
}

void GameRuleManager::level1() {
	Player* m_player = new Player();
	m_player->init({ 3, 7 });
	m_ChessList.push_back(m_player);

	ChessPiece* m_king = new ChessPiece("W_King");
	m_king->init({ 3, 0 });
	m_king->setHealth(m_healthList[PIECETYPE::QUEEN]);
	m_ChessList.push_back(m_king);

	for (int i = 2; i <= 5; i++) {
		ChessPiece* m_pawn = new ChessPiece("W_Pawn");
		m_pawn->init({ i, 1 });
		m_ChessList.push_back(m_pawn);
	}

	ChessPiece* m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 4, 0 });
	m_ChessList.push_back(m_knight);
}

void GameRuleManager::level2() {
	Player* m_player = new Player();
	m_player->init({ 4, 7 });
	m_ChessList.push_back(m_player);

	ChessPiece* m_king = new ChessPiece("W_King");
	m_king->init({ 3, 0 });
	m_ChessList.push_back(m_king);

	for (int i = 2; i <= 5; i++) {
		ChessPiece* m_pawn = new ChessPiece("W_Pawn");
		m_pawn->init({ i, 1 });
		m_ChessList.push_back(m_pawn);
	}

	ChessPiece* m_bishop = new ChessPiece("W_Bishop");
	m_bishop->init({ 2, 0 });
	m_ChessList.push_back(m_bishop);

	ChessPiece* m_rook = new ChessPiece("W_Rook");
	m_rook->init({ 4, 0 });
	m_ChessList.push_back(m_rook);

	ChessPiece* m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 5, 0 });
	m_ChessList.push_back(m_knight);
}

void GameRuleManager::level3() {
	Player* m_player = new Player();
	m_player->init({ 3, 7 });
	m_ChessList.push_back(m_player);

	ChessPiece* m_king = new ChessPiece("W_King");
	m_king->init({ 3, 0 });
	m_ChessList.push_back(m_king);

	for (int i = 1; i <= 6; i++) {
		ChessPiece* m_pawn = new ChessPiece("W_Pawn");
		m_pawn->init({ i, 1 });
		m_ChessList.push_back(m_pawn);
	}

	for (int i = 0; i <= 7; i += 7) {
		ChessPiece* m_rook = new ChessPiece("W_Rook");
		m_rook->init({ i, 0 });
		m_ChessList.push_back(m_rook);
	}

	for (int i = 2; i <= 5; i += 3) {
		ChessPiece* m_bishop = new ChessPiece("W_Bishop");
		m_bishop->init({ i, 0 });
		m_ChessList.push_back(m_bishop);
	}

	ChessPiece* m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 4, 0 });
	m_ChessList.push_back(m_knight);
}

void GameRuleManager::level4() {
	Player* m_player = new Player();
	m_player->init({ 3, 7 });
	m_ChessList.push_back(m_player);

	ChessPiece* m_king = new ChessPiece("W_King");
	m_king->init({ 3, 0 });
	m_ChessList.push_back(m_king);

	for (int i = 2; i <= 5; i++) {
		ChessPiece* m_pawn = new ChessPiece("W_Pawn");
		m_pawn->init({ i, 1 });
		m_ChessList.push_back(m_pawn);
	}

	ChessPiece* m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 0, 0 });
	m_ChessList.push_back(m_knight);

	m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 6, 0 });
	m_ChessList.push_back(m_knight);

	m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 7, 0 });
	m_ChessList.push_back(m_knight);

	for (int i = 1; i <= 5; i += 4) {
		ChessPiece* m_bishop = new ChessPiece("W_Bishop");
		m_bishop->init({ i, 0 });
		m_ChessList.push_back(m_bishop);
	}

	for (int i = 2; i <= 4; i += 2) {
		ChessPiece* m_rook = new ChessPiece("W_Rook");
		m_rook->init({ i, 0 });
		m_ChessList.push_back(m_rook);
	}
}

void GameRuleManager::level5() {
	Player* m_player = new Player();
	m_player->init({ 3, 7 });
	m_ChessList.push_back(m_player);

	ChessPiece* m_king = new ChessPiece("W_King");
	m_king->init({ 3, 0 });
	m_ChessList.push_back(m_king);

	ChessPiece* m_queen = new ChessPiece("W_Queen");
	m_queen->init({ 4, 0 });
	m_ChessList.push_back(m_queen);

	for (int i = 0; i <= 7; i++) {
		ChessPiece* m_pawn = new ChessPiece("W_Pawn");
		m_pawn->init({ i, 1 });
		m_ChessList.push_back(m_pawn);
	}

	for (int i = 0; i <= 7; i += 7) {
		ChessPiece* m_rook = new ChessPiece("W_Rook");
		m_rook->init({ i, 0 });
		m_ChessList.push_back(m_rook);
	}

	for (int i = 1; i <= 6; i += 5) {
		ChessPiece* m_knight = new ChessPiece("W_Knight");
		m_knight->init({ i, 0 });
		m_ChessList.push_back(m_knight);
	}

	for (int i = 2; i <= 5; i += 3) {
		ChessPiece* m_bishop = new ChessPiece("W_Bishop");
		m_bishop->init({ i, 0 });
		m_ChessList.push_back(m_bishop);
	}
}

int GameRuleManager::getShotgunDMG() {
	return m_shotgunDamage;
}

void GameRuleManager::setShotgunDMG(int value) {
	m_shotgunDamage = value;
}

int GameRuleManager::getShotgunSpray() {
	return m_shotgunSpray;
}

void GameRuleManager::setShotgunSpray(int value) {
	m_shotgunSpray = value;
}

int GameRuleManager::getShotgunRange() {
	return m_shotgunRange;
}

void GameRuleManager::setShotgunRange(int value) {
	m_shotgunRange = value;
}

int GameRuleManager::getShotgunMaxAmmo() {
	return m_shotgunMaxAmmo;
}

void GameRuleManager::setShotgunMaxAmmo(int value) {
	m_shotgunMaxAmmo = value;
}

int GameRuleManager::getShotgunMaxCapacity() {
	return m_shotgunMaxCapacity;
}

void GameRuleManager::setShotgunMaxCapacity(int value) {
	m_shotgunMaxCapacity = value;
}

int GameRuleManager::getPriceChess(PIECETYPE type) {
	return m_priceList[type];
}

void GameRuleManager::setPriceChess(PIECETYPE type, int price) {
	m_priceList[type] = price;
}

int GameRuleManager::getHealthChess(PIECETYPE type) {
	return m_healthList[type];
}

void GameRuleManager::setHealthChess(PIECETYPE type, int health) {
	m_healthList[type] = health;
}

int GameRuleManager::getQueueSizeChess(PIECETYPE type) {
	return m_queueSizeList[type];
}

void GameRuleManager::setQueueSizeChess(PIECETYPE type, int size) {
	m_queueSizeList[type] = size;
}

int GameRuleManager::getCurrentLevel() {
	return m_currentLevel;
}

std::vector<ChessPiece*>& GameRuleManager::getChessList(int level) {
	levelInit(level);
	return m_ChessList;
}
