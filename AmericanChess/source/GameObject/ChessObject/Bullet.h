#pragma once
#include "../../GameManager/WindowConnector.h"
#include "../../Misc/GameMath.h"
#include "../../GameConfig.h"

class Bullet {
public:
	Bullet();
	~Bullet();

	void init(sf::Vector2f pos, float angle);
	void update(float deltaTime);
	void render();

	sf::Vector2f getHitbox();
	bool isFlying();
	void stop();

	int getDamage();
private:
	float m_currentTime;

	bool m_isFlying;
	bool m_isVisible;

	float m_angle;
	sf::Vector2f m_shootPos;
	sf::VertexArray m_bulletLine;
};