#pragma once
#include "Singleton.h"
#include <iostream>
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#define DATA ResourceManager::GetInstance()

class ResourceManager: public Singleton<ResourceManager> {
public:
	ResourceManager();
	~ResourceManager();

	void addTexture(std::string name);
	void removeTexture(std::string name);
	sf::Texture* getTexture(std::string name);
	bool hasTexture(std::string name);

	void addFont(std::string name);
	void removeFont(std::string name);
	sf::Font* getFont(std::string name);
	bool hasFont(std::string name);

	void addSound(std::string name);
	void removeSound(std::string name);
	sf::Sound* getSound(std::string name);
	bool hasSound(std::string name);
	void playSound(std::string name);
	
	bool isSoundEnable();
	void enableSound();
	void disableSound();

	void setCursor(std::string name);
	sf::Image* getCursor();

	void preload();
private:
	bool m_isPreloaded;

	bool m_isSoundEnable;

	sf::Image* m_customCursor;

	std::map<std::string, sf::Texture*> m_MapTexture;
	std::map<std::string, sf::Font*> m_MapFont;
	std::map<std::string, sf::Sound*> m_MapSound;

	std::string m_Path;
	std::string m_TexturePath;
	std::string m_FontPath;
	std::string m_SoundPath;
};

