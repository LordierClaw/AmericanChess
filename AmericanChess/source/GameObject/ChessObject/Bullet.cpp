#include "Bullet.h"
#include "../GameRuleManager.h"

Bullet::Bullet() {
	m_currentTime = 0;
	m_angle = 0;
	m_isVisible = false;
	m_isFlying = false;
}

Bullet::~Bullet() {
}

void Bullet::init(sf::Vector2f pos, float angle) {
	m_angle = angle;
	m_shootPos = pos;
	m_bulletLine.resize(2);
	m_bulletLine.setPrimitiveType(sf::LineStrip);
	m_isVisible = true;
	m_isFlying = true;
	m_bulletLine[0] = sf::Vertex(pos, sf::Color::Red);
	m_bulletLine[1] = sf::Vertex(pos, sf::Color::Yellow);
}

void Bullet::update(float deltaTime) {
	m_currentTime += deltaTime;
	float range = GameRule->getShotgunRange() * 2/ 3;
	float velocity = (float)SHOOTING_DURATION / range;
	
	if (m_currentTime < SHOOTING_DURATION/2) {
		if (m_isFlying == true) {
		float offset = range * (m_currentTime / (SHOOTING_DURATION / 2));
			m_bulletLine[1].position.x = m_shootPos.x + offset * cos(m_angle);
			m_bulletLine[1].position.y = m_shootPos.y + offset * sin(m_angle);
		}
	} else if (m_currentTime < SHOOTING_DURATION) {
		float offset = range * (m_currentTime / (SHOOTING_DURATION / 2) - 1);
		float x = m_shootPos.x + offset * cos(m_angle);
		float y  = m_shootPos.y + offset * sin(m_angle);
		m_bulletLine[0].position.x = x;
		m_bulletLine[0].position.y = y;
	} else {
		m_isVisible = false;
		m_isFlying = false;
		m_currentTime = 0;
		return;
	}
}

void Bullet::render() {
	WConnect->getWindow()->draw(m_bulletLine);
}

sf::Vector2f Bullet::getHitbox() {
	return m_bulletLine[1].position;
}

bool Bullet::isFlying() {
	return m_isFlying;
}

void Bullet::stop() {
	m_isFlying = false;
}

int Bullet::getDamage() {
	float r = GameMath::getDistance(m_shootPos, m_bulletLine[1].position);
	int damage = round(GameRule->getShotgunDMG() * (1 - r / GameRule->getShotgunRange()));

	if (damage < 0) damage = 0;
	else if (damage > GameRule->getShotgunDMG()) damage = GameRule->getShotgunDMG();

	return damage;
}
