#pragma once
#include "../../GameManager/ResourceManager.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>

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

	int getCurrentAmmo();
	int getMaxAmmo();
	void addAmmo();

	int getCurrentCapacity();
	int getMaxCapacity();
	void addCapacity();

	std::vector<Bullet*>& getBullets();
private:
	Player* m_player;

	float m_currentTime;

	std::vector<Bullet*> m_bullets;
	int m_currentAmmo;
	int m_maxAmmo;
	int m_currentCapacity;
	int m_maxCapacity;

	bool m_isShootable;
	bool m_isShooting;
	bool m_isFinishShoot;

	void handleRotateGun(sf::Vector2f mousePosition, float deltaTime);
	void handleShoot(sf::Vector2f mousePosition, float deltaTime);
	
	sf::VertexArray m_RangeGun;
	sf::RectangleShape m_RangeLineL;
	sf::RectangleShape m_RangeLineR;
	void handleDrawRange(sf::Vector2f mousePosition, float deltaTime);
};