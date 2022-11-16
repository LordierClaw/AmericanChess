#pragma once
#include "../../GameManager/ResourceManager.h"
#include "../../GameManager/WindowConnector.h"
#include "Shotgun.h"

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

	sf::Text m_lblAmmo;
};