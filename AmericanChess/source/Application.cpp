#include "Application.h"

Application::Application() {
	m_window = nullptr;
}

Application::~Application() {
	if (m_window != nullptr) delete m_window;
}

void Application::init() {
	//graphic
	m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WITDH, SCREEN_HEIGHT), GAME_TITLE, sf::Style::Close);
	m_window->setFramerateLimit(FRAMERATE_LIMIT);
	m_window->setVerticalSyncEnabled(VERTICAL_SYNC);
	m_window->setIcon(128, 128, DATA->getTexture("icon")->copyToImage().getPixelsPtr());
	//custom cursor
	DATA->setCursor("cursor/target");
	sf::Cursor* gameCursor = new sf::Cursor();
	sf::Vector2u cursorSize = DATA->getCursor()->getSize();
	gameCursor->loadFromPixels(DATA->getCursor()->getPixelsPtr(), cursorSize, sf::Vector2u(cursorSize.x/2, cursorSize.y/2));
	m_window->setMouseCursor(*gameCursor);

	//game start
	WConnect->setWindow(m_window);
	GSM->changeState(StateTypes::INTRO);
}

void Application::update(float deltaTime) {
	if (GSM->needToChangeState()) GSM->performSateChange();
	GSM->currentState()->update(deltaTime);
}

void Application::render() {
	m_window->clear();
	GSM->currentState()->render();
	m_window->display();
}

void Application::run() {
	init();

	sf::Clock clock;
	float deltaTime = 0.f;

	while (m_window->isOpen()) {
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) m_window->close();
		}
		update(deltaTime);
		render();
	}
}