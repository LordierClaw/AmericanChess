#pragma once
#include "../GameManager/ResourceManager.h"
#include "../GameManager/WindowConnector.h"

class SoundButton :public sf::RectangleShape {
public:
	SoundButton();
	~SoundButton();

	void init();
	void update(float deltaTime);
	void render();
private:
	bool m_isHandling;
	float m_currentTime;

	bool m_sound;
};