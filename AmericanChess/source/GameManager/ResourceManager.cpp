#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	m_Path = "../Data/";
	m_TexturePath = m_Path + "Texture/";
	m_FontPath = m_Path + "Font/";
	m_SoundPath = m_Path + "Sound/";
	m_isSoundEnable = true;
	m_isPreloaded = false;
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
	if (m_MapTexture.count(name)) return;
	m_MapTexture.insert({ name, texture });
}

void ResourceManager::removeTexture(std::string name) {
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) return;
	if (it->second == nullptr) return;
	else delete it->second;
	m_MapTexture.erase(it);
}

sf::Texture* ResourceManager::getTexture(std::string name) {
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) {
		addTexture(name);
		return getTexture(name);
	}
	return it->second;
}

bool ResourceManager::hasTexture(std::string name) {
	return m_MapTexture.count(name);
}

void ResourceManager::addFont(std::string name) {
	sf::Font* font = new sf::Font;
	font->loadFromFile(m_FontPath + name + ".ttf");
	if (m_MapFont.count(name)) return;
	m_MapFont.insert({ name, font });
}

void ResourceManager::removeFont(std::string name) {
	auto it = m_MapFont.find(name);
	if (it == m_MapFont.end()) return;
	if (it->second == nullptr) return;
	else delete it->second;
	m_MapFont.erase(it);
}

sf::Font* ResourceManager::getFont(std::string name) {
	auto it = m_MapFont.find(name);
	if (it == m_MapFont.end()) {
		addFont(name);
		return getFont(name);
	}
	return it->second;
}

bool ResourceManager::hasFont(std::string name) {
	return m_MapFont.count(name);
}

void ResourceManager::addSound(std::string name) {
	sf::Sound* sound = new sf::Sound;
	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	buffer->loadFromFile(m_SoundPath + name + ".wav");
	sound->setBuffer(*buffer);
	if (m_MapSound.count(name)) return;
	m_MapSound.insert({ name, sound });
}

void ResourceManager::removeSound(std::string name) {
	auto it = m_MapSound.find(name);
	if (it == m_MapSound.end()) return;
	if (it->second == nullptr) return;
	else delete it->second;
	m_MapSound.erase(it);
}

sf::Sound* ResourceManager::getSound(std::string name) {
	auto it = m_MapSound.find(name);
	if (it == m_MapSound.end()) {
		addSound(name);
		return getSound(name);
	}
	return it->second;
}

bool ResourceManager::hasSound(std::string name) {
	return m_MapSound.count(name);
}

void ResourceManager::playSound(std::string name) {
	if (m_isSoundEnable) this->getSound(name)->play();
}

bool ResourceManager::isSoundEnable() {
	return m_isSoundEnable;
}

void ResourceManager::enableSound() {
	m_isSoundEnable = true;
}

void ResourceManager::disableSound() {
	m_isSoundEnable = false;
}

void ResourceManager::setCursor(std::string name) {
	if (m_customCursor != nullptr) delete m_customCursor;
	m_customCursor = new sf::Image();
	m_customCursor->loadFromFile(m_TexturePath + name + ".png");
}

sf::Image* ResourceManager::getCursor() {
	return m_customCursor;
}

void ResourceManager::preload() {
	if (m_isPreloaded) return;
	//FONT
	this->addFont("Silver");
	//SOUND
	std::vector<std::string> m_soundList = {
		"cash",
		"drop1",
		"drop2",
		"drop3",
		"shoot",
		"smb_gameover",
		"smb_stage_clear",
	};
	for (auto sound : m_soundList) {
		this->addSound(sound);
	}
	//TEXTURE
	std::vector<std::string> m_textureList = {
		"bg-about",
		"bg-dead",
		"bg-end",
		"bg",
		"bg2",
		"intro",
		"logo",
		"chess/Board",
		"chess/CashCounter",
		"chess/MoveBox",
		"chess/card/B_Cardbox",
		"chess/card/W_Cardbox",
		"chess/gun/Bullet-empty",
		"chess/gun/Bullet-filled",
		"chess/gun/Shotgun",
		"chess/piece/B_Bishop",
		"chess/piece/B_King",
		"chess/piece/B_Knight",
		"chess/piece/B_Pawn",
		"chess/piece/B_Queen",
		"chess/piece/B_Rook",
		"chess/piece/W_Bishop",
		"chess/piece/W_King",
		"chess/piece/W_Knight",
		"chess/piece/W_Pawn",
		"chess/piece/W_Queen",
		"chess/piece/W_Rook",
		"cursor/point",
		"cursor/shoot",
		"cursor/target",
		"gui/btnAbout_handle",
		"gui/btnAbout_idle",
		"gui/btnBackToMenu_handle",
		"gui/btnBackToMenu_idle",
		"gui/btnContinue_handle",
		"gui/btnContinue_idle",
		"gui/btnEasy_handle",
		"gui/btnEasy_idle",
		"gui/btnExit_handle",
		"gui/btnExit_idle",
		"gui/btnHard_handle",
		"gui/btnHard_idle",
		"gui/btnHome_handle",
		"gui/btnHome_idle",
		"gui/btnMenu_handle",
		"gui/btnMenu_idle",
		"gui/btnNormal_handle",
		"gui/btnNormal_idle",
		"gui/btnPlay_handle",
		"gui/btnPlay_idle",
		"gui/btnSound_disable",
		"gui/btnSound_enable",
		"gui/shopBoard",
	};
	for (auto texture : m_textureList) {
		if (this->hasTexture(texture) == false) this->addTexture(texture);
	}

	//PRELOADED
	m_isPreloaded = true;
}
