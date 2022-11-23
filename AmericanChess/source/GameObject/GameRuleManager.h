#pragma once
#include "../GameManager/Singleton.h"
#include "ChessObject/Player.h"
#include "ChessObject/Shotgun.h"
#include <map>

#define GameRule GameRuleManager::GetInstance()

enum GAMEMODE {
	EASY = 0,
	NORMAL,
	HARD
};

class GameRuleManager : public Singleton<GameRuleManager> {
public:
	GameRuleManager();
	~GameRuleManager();
	void setMode(GAMEMODE mode);
private:
	void levelInit(int n);
	void level1();
	void level2();
	void level3();
	void level4();
	void level5();

//PLAYER SETTING
public:
	int getShotgunDMG();
	void setShotgunDMG(int value);

	int getShotgunSpray();
	void setShotgunSpray(int value);

	int getShotgunRange();
	void setShotgunRange(int value);

	int getShotgunMaxAmmo();
	void setShotgunMaxAmmo(int value);

	int getShotgunMaxCapacity();
	void setShotgunMaxCapacity(int value);
private:
	int m_shotgunDamage;
	int m_shotgunSpray;
	int m_shotgunRange;
	int m_shotgunMaxAmmo;
	int m_shotgunMaxCapacity;

//CHESS SETTING
public:
	int getPriceChess(PIECETYPE type);
	void setPriceChess(PIECETYPE type, int price);

	int getHealthChess(PIECETYPE type);
	void setHealthChess(PIECETYPE type, int health);

	int getQueueSizeChess(PIECETYPE type);
	void setQueueSizeChess(PIECETYPE type, int size);
private:
	std::map<PIECETYPE, int> m_priceList;
	std::map<PIECETYPE, int> m_healthList;
	std::map<PIECETYPE, int> m_queueSizeList;

//GAME LEVEL
public:
	int getCurrentLevel();
	std::vector<ChessPiece*>& getChessList(int level);
private:
	int m_currentLevel;
	// level n must be between 1-5
	std::vector<ChessPiece*> m_ChessList;
};