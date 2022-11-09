#include "GSMenu.h"

GSMenu::GSMenu() {
	DATA->addTexture("bg");
	DATA->addTexture("logo");
}

GSMenu::~GSMenu() {
}

void GSMenu::exit() {
}

void GSMenu::pause() {
}

void GSMenu::resume() {
}

void GSMenu::init() {
	//transition
	m_blackScreen = new sf::RectangleShape(sf::Vector2f(SCREEN_WITDH, SCREEN_HEIGHT));
	m_blackScreen->setFillColor(sf::Color::Black);
	isPerformTransition = true;
	m_currentTime = 0;
	//background
	m_background.setTexture(*DATA->getTexture("bg"));
	sf::Color bgColor = m_background.getColor();
	m_background.setColor(bgColor);
	//logo
	m_logo.setTexture(*DATA->getTexture("logo"));
	m_logo.setOrigin(sf::Vector2f(282.f/2, 144.f/2));
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

	//play button
	GameButton* playBtn = new GameButton("btnPlay", sf::Vector2f(61.f, 36.f));
	playBtn->init();
	playBtn->setPosition(sf::Vector2f(640.f, 500.f));
	playBtn->setOnClick([]() {GSM->changeState(PLAY); });
	m_btnList.push_back(playBtn);

	//about button
	GameButton* aboutBtn = new GameButton("btnAbout", sf::Vector2f(79.f, 36.f));
	aboutBtn->init();
	aboutBtn->setPosition(sf::Vector2f(640.f, 540.f));
	aboutBtn->setOnClick([]() { });
	m_btnList.push_back(aboutBtn);

	//exit button
	GameButton* exitBtn = new GameButton("btnExit", sf::Vector2f(61.f, 32.f));
	exitBtn->init();
	exitBtn->setPosition(sf::Vector2f(640.f, 580.f));
	exitBtn->setOnClick([]() {WConnect->getWindow()->close(); });
	m_btnList.push_back(exitBtn);
}

void GSMenu::update(float deltaTime) {
	//transition
	if (isPerformTransition == true) {
		m_currentTime += deltaTime;
		if (m_currentTime < TRANSITION_DURATION) {
			sf::Color color = sf::Color::Black;
			color.a = 255 * (1 - (m_currentTime / TRANSITION_DURATION));
			m_blackScreen->setFillColor(color);
		} else {
			isPerformTransition = false;
			m_blackScreen->setFillColor(sf::Color::Transparent);
			m_currentTime = 0;
			delete m_blackScreen;
		}
	}
	//menu update
	for (auto& btn : m_btnList) {
		btn->update(deltaTime);
	}
	m_player->update(deltaTime);
}

void GSMenu::render() {
	//logo
	WConnect->getWindow()->draw(m_background);
	WConnect->getWindow()->draw(m_logo);
	m_player->render();
	//button
	for (auto& btn : m_btnList) {
		btn->render();
	}
	//transition
	if (isPerformTransition) WConnect->getWindow()->draw(*m_blackScreen);
}
