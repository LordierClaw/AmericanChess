#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	m_Path = "../Data/";
	m_TexturePath = m_Path + "Texture/";
	m_FontPath = m_Path + "Font/";
}

ResourceManager::~ResourceManager() {
	for (auto it : m_MapTexture) {
		if (it.second != nullptr) delete it.second;
	}
	m_MapTexture.clear();
}

void ResourceManager::addTexture(std::string name) {
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(m_TexturePath + name + ".png");
	if (m_MapTexture.count(name)) {
		std::cout << "Failed to add texture: " << name <<  " already exists \n";
		return;
	}
	m_MapTexture.insert({ name, texture });
	std::cout << "Add texture successfully: " << name << "\n";
}

void ResourceManager::removeTexture(std::string name) {
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) {
		std::cout << "Failed to remove texture: " << name << " doesn't exist\n";
		return;
	}
	if (it->second == nullptr) {
		std::cout << "Failed to remove texture: " << name << " null pointer\n";
		return;
	} else delete it->second;
	m_MapTexture.erase(it);
	std::cout << "Remove texture successfully: " << name << "\n";
}

sf::Texture* ResourceManager::getTexture(std::string name) {
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) {
		std::cout << "Failed to load texture: " << name << " doesn't exist\n";
		return nullptr;
	}
	return it->second;
}

bool ResourceManager::hasTexture(std::string name) {
	return m_MapTexture.count(name);
}

void ResourceManager::setCursor(std::string name) {
	if (m_customCursor != nullptr) delete m_customCursor;
	m_customCursor = new sf::Image();
	m_customCursor->loadFromFile(m_TexturePath + name + ".png");
}

sf::Image* ResourceManager::getCursor() {
	return m_customCursor;
}
