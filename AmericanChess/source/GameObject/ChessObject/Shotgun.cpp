#include "Shotgun.h"
#include <cstdlib>

Shotgun::Shotgun() {
	m_isShooting = false;
	m_currentTime = 0;
	m_isShootable = false;
	m_isFinishShoot = false;
	m_player = nullptr;
}

Shotgun::Shotgun(Player* player) : Shotgun() {
	m_player = player;
}

Shotgun::~Shotgun() {
}

void Shotgun::init() {
	DATA->addTexture("chess/gun/Shotgun");
	this->setTexture(*DATA->getTexture("chess/gun/Shotgun"));
	this->setOrigin(sf::Vector2f(8.f, 8.f));
	this->setScale(sf::Vector2f(2.f, 2.f));
	m_isShootable = true;
	m_isShooting = false;
	m_isFinishShoot = false;
	//
	m_bullets.resize(10);
}

void Shotgun::sync() {
	this->setPosition(m_player->getPosition());
	sf::Color gunColor = this->getColor();
	gunColor.a = m_player->getColor().a;
	this->setColor(gunColor);
}

void Shotgun::update(float deltaTime) {
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow());
	if (m_isFinishShoot) {
		handleRotateGun(mousePosition, deltaTime);
		return;
	}
	if (m_isShooting) {
		handleShoot(mousePosition, deltaTime);
		return;
	}
	
	handleRotateGun(mousePosition, deltaTime);
	if (m_isShootable) handleDrawRange(mousePosition, deltaTime);
}

void Shotgun::render() {
	if (m_isShootable && !m_isShooting) {
		WConnect->getWindow()->draw(m_RangeGun);
		WConnect->getWindow()->draw(m_RangeLineL);
		WConnect->getWindow()->draw(m_RangeLineR);
	}
	if (m_isShooting) {
		for (auto bullet : m_bullets) {
			bullet->render();
		}
	}
	WConnect->getWindow()->draw(*this);
}

void Shotgun::shoot() {
	srand(time(NULL));
	sf::Vector2f pos = this->getPosition();

	for (int i = 0; i < 10; i++) {
		Bullet* bullet = new Bullet();
		float angle = this->getRotation();
		int range = SHOOTING_RANGE_ANGLE*7/9;
		angle = (angle + rand() % range) - range / 2;
		angle = GameMath::degreeToRad(angle);
		pos.x += 8.f * cos(angle);
		pos.y += 8.f * sin(angle);
		bullet->init(pos, angle);
		if (m_bullets[i] != nullptr) delete m_bullets[i];
		m_bullets[i] = bullet;
	}

	m_isShooting = true;
}

void Shotgun::setShootable(bool value) {
	m_isShootable = value;
}

void Shotgun::reset() {
	m_isShootable = true;
	m_isShooting = false;
	m_isFinishShoot = false;
	for (auto bullet : m_bullets) {
		if (bullet != nullptr) delete bullet;
	}
	m_bullets.clear();
	m_bullets.resize(10);
}

bool Shotgun::finishShoot() {
	return m_isFinishShoot;
}

std::vector<Bullet*>& Shotgun::getBullets() {
	return this->m_bullets;
}

void Shotgun::handleRotateGun(sf::Vector2f mousePosition, float deltaTime) {
	float angle = GameMath::radToDegree(GameMath::getAngle(this->getPosition(), mousePosition));
	this->setRotation(angle);
	//flip gun
	if (angle < 90.f || angle > 270.f) this->setScale(sf::Vector2f(2.f, 2.f));
	else this->setScale(sf::Vector2f(2.f, -2.f));
}

void Shotgun::handleShoot(sf::Vector2f mousePostion, float deltaTime) {
	m_currentTime += deltaTime;
	if (m_currentTime <= SHOOTING_DURATION) {
		float x = GameMath::getHarmonicMotion(SHOOTING_OFFSET, SHOOTING_DURATION, m_currentTime);
		this->setOrigin(sf::Vector2f(8.f - x, 8.f));
		for (auto bullet : m_bullets) bullet->update(deltaTime);
	} else {
		this->setOrigin(sf::Vector2f(8.f, 8.f));
		m_currentTime = 0;
		m_isShooting = false;
		m_isFinishShoot = true;
		m_player->endTurn();
	}
}

void Shotgun::handleDrawRange(sf::Vector2f mousePosition, float deltaTime) {
	float angle = GameMath::radToDegree(GameMath::getAngle(this->getPosition(), mousePosition));
	//the curve
	sf::VertexArray lineCurve(sf::TriangleStrip);
	float angleL = angle - SHOOTING_RANGE_ANGLE / 2, angleR = angle + SHOOTING_RANGE_ANGLE / 2;
	float r = std::min((float)SHOOTING_MAX_RANGE, GameMath::getDistance(this->getPosition(), mousePosition) - 25.f);

	int t = SHOOTING_RANGE_THICKNESS;
	for (float i = angleL; i <= angleR; i += 0.05f) {
		if (t == SHOOTING_RANGE_THICKNESS) t = 0;
		else t = SHOOTING_RANGE_THICKNESS;
		// use t to calculate connected point of triangles
		float x = this->getPosition().x + (r-t) * cos(PI * 2 * i / 360);
		float y = this->getPosition().y + (r-t) * sin(PI * 2 * i / 360);
		lineCurve.append(sf::Vertex(sf::Vector2f(x, y), SHOOTING_RANGE_COLOR));
	}
	m_RangeGun = lineCurve;
	sf::RectangleShape lineL(sf::Vector2f(r / 5, (float)SHOOTING_RANGE_THICKNESS));
	sf::RectangleShape lineR(sf::Vector2f(r / 5, (float)SHOOTING_RANGE_THICKNESS));
	
	//draw 2 lines
	lineL.setOrigin(sf::Vector2f((float)SHOOTING_RANGE_THICKNESS / 2, 0));
	lineR.setOrigin(lineL.getOrigin());
	
	float xl = this->getPosition().x + (r*0.85) * cos(PI * 2 * angleL / 360);
	float yl = this->getPosition().y + (r*0.85) * sin(PI * 2 * angleL / 360);
	float xr = this->getPosition().x + (r*0.85) * cos(PI * 2 * angleR / 360);
	float yr = this->getPosition().y + (r*0.85) * sin(PI * 2 * angleR / 360);
	
	lineL.setPosition(sf::Vector2f(xl, yl));
	lineR.setPosition(sf::Vector2f(xr, yr));
	lineL.setFillColor(SHOOTING_RANGE_COLOR);
	lineR.setFillColor(SHOOTING_RANGE_COLOR);
	lineL.rotate(angleL);
	lineR.rotate(angleR);

	m_RangeLineL = lineL;
	m_RangeLineR = lineR;
}