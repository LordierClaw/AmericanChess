#include "GSModeSelect.h"

GSModeSelect::GSModeSelect() {
}

GSModeSelect::~GSModeSelect() {
}

void GSModeSelect::exit() {
}

void GSModeSelect::pause() {
}

void GSModeSelect::resume() {
}

void GSModeSelect::init() {
	//transition
	m_blackScreen = new sf::RectangleShape(sf::Vector2f(SCREEN_WITDH, SCREEN_HEIGHT));
	m_blackScreen->setFillColor(sf::Color::Black);
	isPerformTransition = true;
	m_currentTime = 0;
	//background
	m_background.setTexture(*DATA->getTexture("bg"));
	//logo
	m_logo.setTexture(*DATA->getTexture("logo"));
	m_logo.setOrigin(sf::Vector2f(282.f / 2, 144.f / 2));
	m_logo.setPosition(sf::Vector2f(SCREEN_WITDH / 2, SCREEN_HEIGHT / 2));
	//player
	m_player = new Player();
	m_player->init({ 0, 0 });
	m_player->setPosition(sf::Vector2f(740.f, 400.f));
	m_player->getGun()->setShootable(false);
	m_player->changeState(STATE::IDLE);
	sf::Color playerColor = m_player->getColor();
	playerColor.a = 255;
	m_player->setColor(playerColor);

	//easy button
	GameButton* easyBtn = new GameButton("btnEasy", sf::Vector2f(65.f, 36.f));
	easyBtn->init();
	easyBtn->setPosition(sf::Vector2f(640.f, 500.f));
	easyBtn->setOnClick([]() {
		GameRule->setMode(EASY);
		GSM->changeState(PLAY);
	});
	m_btnList.push_back(easyBtn);

	//normal button
	GameButton* normalBtn = new GameButton("btnNormal", sf::Vector2f(89.f, 32.f));
	normalBtn->init();
	normalBtn->setPosition(sf::Vector2f(640.f, 540.f));
	normalBtn->setOnClick([]() {
		GameRule->setMode(NORMAL);
		GSM->changeState(PLAY);
	});
	m_btnList.push_back(normalBtn);

	//hard button
	GameButton* hardBtn = new GameButton("btnHard", sf::Vector2f(65.f, 32.f));
	hardBtn->init();
	hardBtn->setPosition(sf::Vector2f(640.f, 580.f));
	hardBtn->setOnClick([]() {
		GameRule->setMode(HARD);
		GSM->changeState(PLAY);
	});
	m_btnList.push_back(hardBtn);

	//sound button
	m_soundBtn.init();
}

void GSModeSelect::update(float deltaTime) {
	//transition
	m_player->update(deltaTime);
	if (isPerformTransition == true) {
		m_currentTime += deltaTime;
		if (m_currentTime < TRANSITION_DURATION * 2) {
			sf::Color color = sf::Color::Black;
			color.a = (int)(255 * (1 - (m_currentTime / (TRANSITION_DURATION * 2))));
			m_blackScreen->setFillColor(color);
		} else {
			isPerformTransition = false;
			m_blackScreen->setFillColor(sf::Color::Transparent);
			m_currentTime = 0;
			delete m_blackScreen;
		}
		return;
	}
	//menu update
	for (auto& btn : m_btnList) {
		btn->update(deltaTime);
	}
	m_soundBtn.update(deltaTime);
}

void GSModeSelect::render() {
	//logo
	WConnect->getWindow()->draw(m_background);
	WConnect->getWindow()->draw(m_logo);
	m_player->render();
	//button
	for (auto& btn : m_btnList) {
		btn->render();
	}
	m_soundBtn.render();
	//transition
	if (isPerformTransition) WConnect->getWindow()->draw(*m_blackScreen);
}
