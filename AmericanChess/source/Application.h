#pragma once
#include "SFML/Graphics.hpp"
#include "GameConfig.h"
#include "GameManager/ResourceManager.h"
#include "GameStateManager/GameStateMachine.h"
#include "GameStateManager/GameStateBase.h"

class Application {
public:
	Application();
	~Application();
	void run();
private:
	sf::RenderWindow* m_window;
	void init();
	void update(float deltaTime);
	void render();
	
	sf::Sprite player;
	sf::Sprite board;
};