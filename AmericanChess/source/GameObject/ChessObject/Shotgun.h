#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "../../GameManager/Singleton.h"
#include "../../GameConfig.h"
#include "../../Misc/GameMath.h"
#include "Player.h"

class Shotgun : public sf::Sprite {
public:
	Shotgun();
	Shotgun(Player* player);
	~Shotgun();
	void init();
	void sync();
	void update(float deltaTime);
	void render();

	void shoot();

	void setShootable(bool value);
	//reset shoot state
	void reset();

	bool finishShoot();
private:
	Player* m_player;

	float m_currentTime;

	bool m_isShootable;
	bool m_isShooting;
	bool m_isFinishShoot;

	void handleRotateGun(sf::Vector2f mousePosition, float deltaTime);
	void handleShoot(sf::Vector2f mousePosition, float deltaTime);
	
	sf::VertexArray* m_RangeGun;
	sf::RectangleShape* m_RangeLineL;
	sf::RectangleShape* m_RangeLineR;
	void handleDrawRange(sf::Vector2f mousePosition, float deltaTime);
};