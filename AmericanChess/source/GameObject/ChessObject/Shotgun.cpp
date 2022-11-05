#include "Shotgun.h"

Shotgun::Shotgun() {
	m_isShooting = false;
	m_currentTime = 0;
	m_RangeGun = nullptr;
	m_RangeLineL = nullptr;
	m_RangeLineR = nullptr;
	m_isShootable = false;
}

Shotgun::Shotgun(Player* player) : Shotgun() {
	m_player = player;
}

Shotgun::~Shotgun() {
	if (m_RangeGun != nullptr) delete m_RangeGun;
	if (m_RangeLineL != nullptr) delete m_RangeLineL;
	if (m_RangeLineR != nullptr) delete m_RangeLineR;
}

void Shotgun::init() {
	DATA->addTexture("chess/gun/Shotgun");
	this->setTexture(*DATA->getTexture("chess/gun/Shotgun"));
	this->setOrigin(sf::Vector2f(8.f, 8.f));
	this->setScale(sf::Vector2f(2.f, 2.f));
	m_isShootable = true;
	m_isShooting = false;
	m_isFinishShoot = false;
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
	WConnect->getWindow()->draw(*this);
	if (m_isShootable && !m_isShooting) {
		WConnect->getWindow()->draw(*m_RangeGun);
		WConnect->getWindow()->draw(*m_RangeLineL);
		WConnect->getWindow()->draw(*m_RangeLineR);
	}
}

void Shotgun::shoot() {
	// do something
	// TODO: write Shotgun.shoot() function
	m_isShooting = true;
}

void Shotgun::setShootable(bool value) {
	m_isShootable = value;
}

void Shotgun::reset() {
	m_isShootable = true;
	m_isShooting = false;
	m_isFinishShoot = false;
}

bool Shotgun::finishShoot() {
	return m_isFinishShoot;
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
	float x = this->getOrigin().x;
	if (m_currentTime <= SHOOTING_DURATION / 2) {
		x = std::min(8.f + SHOOTING_RECOIL, x + m_currentTime * SHOOTING_RECOIL);
		this->setOrigin(sf::Vector2f(x, 8.f));
	} else if (m_currentTime <= SHOOTING_DURATION) {
		x = std::max(8.f, x - (m_currentTime - SHOOTING_DURATION / 2) * SHOOTING_RECOIL);
		this->setOrigin(sf::Vector2f(x, 8.f));
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
	sf::VertexArray* lineCurve = new sf::VertexArray(sf::TriangleStrip);
	float angleL = angle - SHOOTING_RANGE_ANGLE / 2, angleR = angle + SHOOTING_RANGE_ANGLE / 2;
	float r = std::min((float)SHOOTING_MAX_RANGE, GameMath::getDistance(this->getPosition(), mousePosition) - 25.f);

	int t = SHOOTING_RANGE_THICKNESS;
	for (float i = angleL; i <= angleR; i += 0.05f) {
		if (t == SHOOTING_RANGE_THICKNESS) t = 0;
		else t = SHOOTING_RANGE_THICKNESS;
		// use t to calculate connected point of triangles
		float x = this->getPosition().x + (r-t) * cos(PI * 2 * i / 360);
		float y = this->getPosition().y + (r-t) * sin(PI * 2 * i / 360);
		lineCurve->append(sf::Vertex(sf::Vector2f(x, y), SHOOTING_RANGE_COLOR));
	}
	m_RangeGun = lineCurve;
	sf::RectangleShape* lineL = new sf::RectangleShape(sf::Vector2f(r / 5, (float)SHOOTING_RANGE_THICKNESS));
	sf::RectangleShape* lineR = new sf::RectangleShape(sf::Vector2f(r / 5, (float)SHOOTING_RANGE_THICKNESS));
	
	//draw 2 lines
	lineL->setOrigin(sf::Vector2f((float)SHOOTING_RANGE_THICKNESS / 2, 0));
	lineR->setOrigin(lineL->getOrigin());
	
	float xl = this->getPosition().x + (r*0.85) * cos(PI * 2 * angleL / 360);
	float yl = this->getPosition().y + (r*0.85) * sin(PI * 2 * angleL / 360);
	float xr = this->getPosition().x + (r*0.85) * cos(PI * 2 * angleR / 360);
	float yr = this->getPosition().y + (r*0.85) * sin(PI * 2 * angleR / 360);
	
	lineL->setPosition(sf::Vector2f(xl, yl));
	lineR->setPosition(sf::Vector2f(xr, yr));
	lineL->setFillColor(SHOOTING_RANGE_COLOR);
	lineR->setFillColor(SHOOTING_RANGE_COLOR);
	lineL->rotate(angleL);
	lineR->rotate(angleR);

	m_RangeLineL = lineL;
	m_RangeLineR = lineR;
}