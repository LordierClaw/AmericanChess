#include "ShopButton.h"

ShopButton::ShopButton() {
    m_isHandling = false;
    m_payable = false;
    m_isHover = false;
    m_price = 0;
    m_currentTime = 0;
}

ShopButton::~ShopButton() {
}

void ShopButton::init(std::string name) {
    m_name = name;
    m_selected.setSize(sf::Vector2f(540.f, 47.f));
    m_selected.setFillColor(sf::Color::White);

    m_lblTitle.setFont(*DATA->getFont("Silver"));
    m_lblTitle.setStyle(sf::Text::Bold);
    m_lblTitle.setFillColor(sf::Color(56, 52, 80));
    m_lblTitle.setCharacterSize(50);
    
    m_lblPrice.setFont(*DATA->getFont("Silver"));
    m_lblPrice.setStyle(sf::Text::Bold);
    m_lblPrice.setFillColor(sf::Color(56, 52, 80));
    m_lblPrice.setCharacterSize(38);

    m_isHandling = false;
    m_payable = false;
}

void ShopButton::init(std::string name, int price) {
    init(name);
    setPrice(price);
}

void ShopButton::update(float deltaTime) {
    std::string newTitle = m_name + ": " + std::to_string(m_btnGetValue());
    m_lblTitle.setString(newTitle);

    if (CCounter->getCurrentCash() < m_price) m_payable = false;
    else m_payable = true;

    if (m_isHandling == true) {
        m_currentTime += deltaTime;
        if (m_currentTime > 0.25f) {
            m_currentTime = 0;
            m_isHandling = false;
        } else return;
    }

    if (m_selected.getGlobalBounds().contains(
        (sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())
    )) {
        m_isHover = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            m_isHandling = true;
            if (m_payable) {
                CCounter->addAmount(-m_price);
                DATA->playSound("cash");
                m_btnClickFunc();
            }
        }
    } else m_isHover = false;
}

void ShopButton::render() {
    if (m_isHover && m_payable) {
        WConnect->getWindow()->draw(m_selected);
        WConnect->getWindow()->draw(m_lblPrice);
    }
    WConnect->getWindow()->draw(m_lblTitle);
}

void ShopButton::setValue(int(*Func)()) {
    m_btnGetValue = Func;
}

void ShopButton::setPrice(int price) {
    m_price = price;
    m_lblPrice.setString("upgrade cost: " + std::to_string(price));
}

void ShopButton::setPosition(sf::Vector2f pos) {
    m_selected.setPosition(pos);
    m_lblTitle.setPosition(pos.x + 12.f, pos.y - 12.f);
    float x = pos.x + m_selected.getSize().x - m_lblPrice.getLocalBounds().width - 12.f;
    m_lblPrice.setPosition(x, pos.y - 6.f);
}

void ShopButton::setOnClick(void(*Func)()) {
    m_btnClickFunc = Func;
}