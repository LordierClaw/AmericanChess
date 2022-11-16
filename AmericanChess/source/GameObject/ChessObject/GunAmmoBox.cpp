#include "GunAmmoBox.h"

GunAmmoBox::GunAmmoBox() {
	m_shotgun = nullptr;
}

GunAmmoBox::~GunAmmoBox() {
}

void GunAmmoBox::init() {
	m_lblAmmo.setPosition(sf::Vector2f(640.f-250.f, 15.f));
	m_lblAmmo.setFont(*DATA->getFont("Silver"));
	m_lblAmmo.setCharacterSize(36);
}

void GunAmmoBox::update(float deltaTime) {
	if (m_shotgun == nullptr) return;
	m_lblAmmo.setString("AMMO: " + std::to_string(m_shotgun->getCurrentAmmo()) + "/" + std::to_string(m_shotgun->getMaxAmmo()) + "\n"
	+ "CAPACITY: " + std::to_string(m_shotgun->getCurrentCapacity()) + "/" + std::to_string(m_shotgun->getMaxCapacity()));
}

void GunAmmoBox::render() {
	if (m_shotgun == nullptr) return;
	WConnect->getWindow()->draw(m_lblAmmo);
}

void GunAmmoBox::setGun(Shotgun* shotgun) {
	m_shotgun = shotgun;
}