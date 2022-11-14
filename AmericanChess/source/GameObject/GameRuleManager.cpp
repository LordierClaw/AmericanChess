#include "GameRuleManager.h"

GameRuleManager::GameRuleManager() {
	reset();
}

GameRuleManager::~GameRuleManager() {
}

void GameRuleManager::reset() {
	m_currentLevel = 0;
	//
	m_shotgunDamage = 4;
	m_shotgunRange = 350;
	m_shotgunSpray = 7;
	//
	m_healthList[PIECETYPE::KING] = 8;
	m_healthList[PIECETYPE::QUEEN] = 6;
	m_healthList[PIECETYPE::BISHOP] = 4;
	m_healthList[PIECETYPE::KNIGHT] = 3;
	m_healthList[PIECETYPE::ROOK] = 5;
	m_healthList[PIECETYPE::PAWN] = 3;
	//
	m_queueSizeList[PIECETYPE::KING] = 4;
	m_queueSizeList[PIECETYPE::QUEEN] = 3;
	m_queueSizeList[PIECETYPE::BISHOP] = 3;
	m_queueSizeList[PIECETYPE::KNIGHT] = 2;
	m_queueSizeList[PIECETYPE::ROOK] = 4;
	m_queueSizeList[PIECETYPE::PAWN] = 5;
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
	m_player->init({ 4, 7 });
	m_ChessList.push_back(m_player);

	ChessPiece* m_king = new ChessPiece("W_King");
	m_king->init({ 3, 0 }, 8, 4, 4);
	m_ChessList.push_back(m_king);

	ChessPiece* m_pawn = new ChessPiece("W_Pawn");
	m_pawn->init({ 2, 1 }, 3, 5, 5);
	m_ChessList.push_back(m_pawn);

	m_pawn = new ChessPiece("W_Pawn");
	m_pawn->init({ 3, 1 }, 3, 3, 5);
	m_ChessList.push_back(m_pawn);

	m_pawn = new ChessPiece("W_Pawn");
	m_pawn->init({ 4, 1 }, 3, 4, 5);
	m_ChessList.push_back(m_pawn);

	m_pawn = new ChessPiece("W_Pawn");
	m_pawn->init({ 5, 1 }, 3, 4, 5);
	m_ChessList.push_back(m_pawn);

	ChessPiece* m_bishop = new ChessPiece("W_Bishop");
	m_bishop->init({ 2, 0 }, 4, 3, 3);
	m_ChessList.push_back(m_bishop);

	ChessPiece* m_rook = new ChessPiece("W_Rook");
	m_rook->init({ 4, 0 }, 5, 4, 4);
	m_ChessList.push_back(m_rook);

	ChessPiece* m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 5, 0 }, 3, 1, 2);
	m_ChessList.push_back(m_knight);
}

void GameRuleManager::level2() {
	Player* m_player = new Player();
	m_player->init({ 4, 7 });
	m_ChessList.push_back(m_player);

	ChessPiece* m_king = new ChessPiece("W_King");
	m_king->init({ 3, 0 }, 8, 4, 4);
	m_ChessList.push_back(m_king);

	ChessPiece* m_knight = new ChessPiece("W_Knight");
	m_knight->init({ 5, 0 }, 3, 1, 2);
	m_ChessList.push_back(m_knight);
}

void GameRuleManager::level3() {
}

void GameRuleManager::level4() {
}

void GameRuleManager::level5() {
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
