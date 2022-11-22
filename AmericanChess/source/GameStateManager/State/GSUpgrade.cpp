#include "GSUpgrade.h"

GSUpgrade::GSUpgrade() {
}

GSUpgrade::~GSUpgrade() {
	for (auto& btn : m_shopBtnList) {
		if (btn != nullptr) delete btn;
	}
	m_shopBtnList.clear();
	if (m_background != nullptr) delete m_background;
	if (m_btnContinue != nullptr) delete m_btnContinue;
}

void GSUpgrade::exit() {
}

void GSUpgrade::pause() {
}

void GSUpgrade::resume() {
}

void GSUpgrade::init() {
	m_background = new sf::Sprite;
	m_background->setTexture(*DATA->getTexture("bg2"));
	sf::Color bgColor = m_background->getColor();
	bgColor.a = 150;
	m_background->setColor(bgColor);
	//
	m_btnContinue = new GameButton("btnContinue", sf::Vector2f(172.f, 62.f));
	m_btnContinue->setPosition(sf::Vector2f(985.f, 520.f));
	m_btnContinue->setOnClick([]() {
		GSM->popState();
		ChessBoard->setLevel(GameRule->getCurrentLevel() + 1); 
	});
	m_btnContinue->init();
	//
	m_title.setFont(*DATA->getFont("Silver"));
	m_title.setStyle(sf::Text::Bold);
	m_title.setCharacterSize(62);
	m_title.setPosition(sf::Vector2f(390.f, 4.f));
	m_title.setString("Merchant's Shop");
	//
	m_shopBoard.setTexture(*DATA->getTexture("gui/shopBoard"));
	m_shopBoard.setOrigin(sf::Vector2f(842.f / 2, 0.f));
	m_shopBoard.setPosition(sf::Vector2f(SCREEN_WITDH/2, 185.f));
	//
	for (int i = 0; i < 5; i++) {
		ShopButton* shopbtn = new ShopButton();
		m_shopBtnList.push_back(shopbtn);
	}

	m_shopBtnList[0]->init("RANGE", 700);
	m_shopBtnList[0]->setValue([]() {return GameRule->getShotgunRange(); });
	m_shopBtnList[0]->setOnClick([]() {GameRule->setShotgunRange(GameRule->getShotgunRange() + 50); });

	m_shopBtnList[1]->init("DAMAGE", 1200);
	m_shopBtnList[1]->setValue([]() {return GameRule->getShotgunDMG(); });
	m_shopBtnList[1]->setOnClick([]() {GameRule->setShotgunDMG(GameRule->getShotgunDMG() + 1); });

	m_shopBtnList[2]->init("PELLETS", 1800);
	m_shopBtnList[2]->setValue([]() {return GameRule->getShotgunSpray(); });
	m_shopBtnList[2]->setOnClick([]() {GameRule->setShotgunSpray(GameRule->getShotgunSpray() + 1); });

	m_shopBtnList[3]->init("MAX AMMO", 2000);
	m_shopBtnList[3]->setValue([]() {return GameRule->getShotgunMaxAmmo(); });
	m_shopBtnList[3]->setOnClick([]() {GameRule->setShotgunMaxAmmo(GameRule->getShotgunMaxAmmo() + 1); });

	m_shopBtnList[4]->init("MAX CAPACITY", 1500);
	m_shopBtnList[4]->setValue([]() {return GameRule->getShotgunMaxCapacity(); });
	m_shopBtnList[4]->setOnClick([]() {GameRule->setShotgunMaxCapacity(GameRule->getShotgunMaxCapacity() + 1); });
	
	for (int i = 0; i < 5; i++) {
		m_shopBtnList[i]->setPosition(sf::Vector2f(482.f, 221.f + 47.f * i));
	}
	
	CCounter->init();
	m_alphaColor = 0;
	updateColor();
}

void GSUpgrade::update(float deltaTime) {
	m_currentTime += deltaTime;
	if (m_currentTime < TRANSITION_DURATION * 2) {
		m_alphaColor = std::min(255, (int)round(255 * m_currentTime / (TRANSITION_DURATION * 2)));
	} else {
		m_alphaColor = 255;
		handleUpgrade(deltaTime);
		return;
	}
	updateColor();
}

void GSUpgrade::render() {
	WConnect->getWindow()->draw(*m_background);
	WConnect->getWindow()->draw(*m_btnContinue);
	WConnect->getWindow()->draw(m_shopBoard);
	WConnect->getWindow()->draw(m_title);
	for (auto btn : m_shopBtnList) {
		btn->render();
	}
	CCounter->render();
}

void GSUpgrade::updateColor() {
	sf::Color color = m_background->getColor();
	color.a = m_alphaColor;
	m_background->setColor(color);

	color = m_btnContinue->getFillColor();
	color.a = m_alphaColor;
	m_btnContinue->setFillColor(color);

	m_shopBoard.getColor();
	color.a = m_alphaColor;
	m_shopBoard.setColor(color);
}

void GSUpgrade::handleUpgrade(float deltaTime) {
	m_btnContinue->update(deltaTime);
	for (auto btn : m_shopBtnList) {
		btn->update(deltaTime);
	}
	CCounter->update(deltaTime);
}
