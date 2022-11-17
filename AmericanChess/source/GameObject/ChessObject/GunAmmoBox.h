#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "Shotgun.h"
#include <vector>

class GunAmmoBox {
public:
	GunAmmoBox();
	~GunAmmoBox();

	void init();
	void update(float deltaTime);
	void render();

	void setGun(Shotgun* shotgun);
private:
	Shotgun* m_shotgun;

	int m_lastCheckAmmo;
	int m_lastCheckCapacity;
	sf::Sprite m_gun;
	std::vector<sf::Sprite> m_ammo;
	std::vector<sf::Sprite> m_capacity;
};