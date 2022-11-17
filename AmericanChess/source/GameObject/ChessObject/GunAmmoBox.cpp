#include "GunAmmoBox.h"

GunAmmoBox::GunAmmoBox() {
	m_shotgun = nullptr;
	m_lastCheckAmmo = m_lastCheckCapacity = 0;
}

GunAmmoBox::~GunAmmoBox() {
}

void GunAmmoBox::init() {
	m_gun.setTexture(*DATA->getTexture("chess/gun/Shotgun"));
	m_gun.setScale(sf::Vector2f(2.f, 2.f));
}

void GunAmmoBox::update(float deltaTime) {
	if (m_shotgun == nullptr) return;
	if (m_shotgun->getCurrentAmmo() != m_lastCheckAmmo) {
		for (int i = 0; i < m_shotgun->getCurrentAmmo(); i++) {
			m_ammo[i].setTexture(*DATA->getTexture("chess/gun/bullet-filled"));
		}
		for (int i = m_shotgun->getCurrentAmmo(); i < m_ammo.size(); i++) {
			m_ammo[i].setTexture(*DATA->getTexture("chess/gun/bullet-empty"));
		}
		m_lastCheckAmmo = m_shotgun->getCurrentAmmo();
	}
	if (m_shotgun->getCurrentCapacity() != m_lastCheckCapacity) {
		for (int i = 0; i < m_shotgun->getCurrentCapacity(); i++) {
			m_capacity[i].setTexture(*DATA->getTexture("chess/gun/bullet-filled"));
		}
		for (int i = m_shotgun->getCurrentCapacity(); i < m_capacity.size(); i++) {
			m_capacity[i].setTexture(*DATA->getTexture("chess/gun/bullet-empty"));
		}
		m_lastCheckCapacity = m_shotgun->getCurrentCapacity();
	}
}

void GunAmmoBox::render() {
	if (m_shotgun == nullptr) return;
	for (auto ammo : m_ammo) WConnect->getWindow()->draw(ammo);
	for (auto ammo: m_capacity) WConnect->getWindow()->draw(ammo);
	WConnect->getWindow()->draw(m_gun);
}

void GunAmmoBox::setGun(Shotgun* shotgun) {
	m_shotgun = shotgun;
	m_ammo.clear();
	m_capacity.clear();

	m_ammo.resize(m_shotgun->getMaxAmmo(), sf::Sprite(*DATA->getTexture("chess/gun/bullet-filled")));
	m_capacity.resize(m_shotgun->getMaxCapacity(), sf::Sprite(*DATA->getTexture("chess/gun/bullet-filled")));
	//actual size: 12x24
	for (int i = 0; i < m_ammo.size(); i++) {
		m_ammo[i].setPosition(sf::Vector2f(390.f + 17.f * i, 30.f));
	}
	for (int i = 0; i < m_capacity.size(); i++) {
		m_capacity[i].setPosition(sf::Vector2f(390.f + 17.f * i, 30.f + 30.f));
	}
	m_lastCheckAmmo = m_ammo.size();
	m_lastCheckCapacity = m_capacity.size();

	m_gun.setPosition(sf::Vector2f(m_ammo.back().getPosition().x + 15.f, m_ammo.back().getPosition().y - 5.f));
}