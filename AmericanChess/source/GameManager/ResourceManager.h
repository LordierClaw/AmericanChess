#pragma once
#include "Singleton.h"
#include <iostream>
#include <map>
#include <string>
#include "SFML/Graphics.hpp"

#define DATA ResourceManager::GetInstance()

class ResourceManager: public Singleton<ResourceManager> {
public:
	ResourceManager();
	~ResourceManager();

	void addTexture(std::string name);
	void removeTexture(std::string name);
	sf::Texture* getTexture(std::string name);
	bool hasTexture(std::string name);

	void setCursor(std::string name);
	sf::Image* getCursor();
private:
	sf::Image* m_customCursor;

	std::map<std::string, sf::Texture*> m_MapTexture;
	std::map<std::string, sf::Font*> m_MapFont;

	std::string m_Path;
	std::string m_TexturePath;
	std::string m_FontPath;
};

