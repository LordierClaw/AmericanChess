#include "ChessPiece.h"
#include "../GameRuleManager.h"

ChessPiece::ChessPiece() {
    m_name = "";
    m_state = IDLE;
    m_currentPos = ChessPosition(0, 0);
    m_type = PAWN;
    m_currentTime = 0;

    m_isEndTurn = true;
}

ChessPiece::ChessPiece(std::string name) {
    this->m_name = "chess/piece/" + name;
    // set chess piece type
    if (name == "B_King") {
        m_type = PLAYER;
        return;
    }
    name = name.substr(2);
    if (name == "King") m_type = KING;
    else if (name == "Queen") m_type = QUEEN;
    else if (name == "Bishop") m_type = BISHOP;
    else if (name == "Knight") m_type = KNIGHT;
    else if (name == "Rook") m_type = ROOK;
    else m_type = PAWN;
}

ChessPiece::~ChessPiece() {
}

void ChessPiece::init(ChessPosition pos) {
    this->setTexture(*DATA->getTexture(this->m_name));
    this->setScale(sf::Vector2f(3.f, 3.f));
    this->setOrigin(sf::Vector2f(16.f/2, 23.f/2));
    this->setCurrentPosition(pos);
    m_state = SHOWUP;
    m_color = this->getColor();
    m_color.a = 0;
    this->setColor(m_color);
    m_isEndTurn = true;
    //only for pawn
    m_isPromotion = false;
    if (m_type == PLAYER) return;
    m_health = GameRule->getHealthChess(m_type);
    m_queueSize = GameRule->getQueueSizeChess(m_type);
    m_turnLeft = GameMath::getRandom(1, m_queueSize);
}

void ChessPiece::init(ChessPosition pos, int health, int turnLeft, int queueSize) {
    init(pos);
    m_health = health;
    m_turnLeft = turnLeft;
    m_queueSize = queueSize;
}

void ChessPiece::update(float deltaTime) {
    switch (m_state) {
    case SHOWUP:
        handleShowUp(deltaTime);
    case IDLE:
        if (m_isPromotion) {
            std::vector<std::string> promoteList = { "W_Queen", "W_Knight", "W_Rook", "W_Bishop" };
            promote(promoteList[GameMath::getRandom(0, promoteList.size()-1)]);
        }
        break;
    case READY_TO_MOVE:
        handleReady(deltaTime);
        break;
    case MOVING:
        handleMove(deltaTime);
        break;
    case HURT:
        handleHurt(deltaTime);
        break;
    case KILL:
        handleKill(deltaTime);
        break;
    case DEAD:
        break;
    default:
        break;
    }
}

void ChessPiece::render() {
    WConnect->getWindow()->draw(*this);
}

STATE ChessPiece::getState() {
    return m_state;
}

void ChessPiece::changeState(STATE state) {
    m_currentTime = 0;
    m_state = state;
}

void ChessPiece::setTurnLeft(int turnLeft) {
    m_turnLeft = turnLeft;
}

void ChessPiece::countTurnLeft() {
    if (this->getType() == PIECETYPE::PLAYER) return;
    m_turnLeft--;
    if (m_turnLeft < 0) m_turnLeft = m_queueSize;
    if (m_turnLeft == 1) this->changeState(STATE::READY_TO_MOVE);
    else this->changeState(STATE::IDLE);
}

int ChessPiece::getTurnLeft() {
    return m_turnLeft;
}

int ChessPiece::getQueueSize() {
    return m_queueSize;
}

void ChessPiece::setHealth(int health) {
    m_health = health;
}

void ChessPiece::takeDamage(int dmg) {
    if (m_state == HURT) return;
    m_health -= dmg;
}

int ChessPiece::getHealth() {
    return m_health;
}

PIECETYPE ChessPiece::getType() {
    return m_type;
}

void ChessPiece::setCurrentPosition(ChessPosition pos) {
    m_currentPos = pos;
    this->setPosition(pos.toPosition());
    m_destPos = pos;
}

ChessPosition ChessPiece::getCurrentPosition() {
    return m_currentPos;
}

void ChessPiece::setShootPosition(ChessPosition pos) {
    m_shootPos = pos;
}

void ChessPiece::setDestPosition(ChessPosition pos) {
    m_destPos = pos;
}

ChessPosition ChessPiece::getDestPosition() {
    return m_destPos;
}

void ChessPiece::performTurn() {
    m_currentTime = 0;
    m_isEndTurn = false;
}

void ChessPiece::endTurn() {
    m_isEndTurn = true;
}

bool ChessPiece::isEndTurn() {
    return m_isEndTurn;
}

void ChessPiece::handleShowUp(float deltaTime) {
    m_currentTime += deltaTime;
    if (m_currentTime < SHOW_UP_DURATION) {
        float offsetY =  GameMath::getHarmonicMotion(SHOW_UP_OFFSET, SHOW_UP_DURATION, m_currentTime);
        sf::Vector2f pos = m_currentPos.toPosition();
        pos.y += offsetY;
        this->setPosition(pos);
    } else {
        this->setCurrentPosition(m_currentPos);
        DATA->playSound("drop1");
    }

    if (m_currentTime < SHOW_UP_DURATION/2) {
        m_color.a = std::min(255, (int)round(255 * m_currentTime / (SHOW_UP_DURATION/2)));
        this->setColor(m_color);
    } else if (m_currentTime > SHOW_UP_DURATION) {
        m_color.a = 255;
        this->setColor(m_color);
        this->changeState(IDLE);
        this->endTurn();
    }
}

void ChessPiece::handleReady(float deltaTime) {
    m_currentTime += deltaTime;
    float x = 8.f + GameMath::getHarmonicMotion(BUZZING_OFFSET, BUZZING_DURATION, m_currentTime);
    this->setOrigin(sf::Vector2f(x, 23.f / 2));
}

void ChessPiece::handleMove(float deltaTime) {
    m_currentTime += deltaTime;
    if (m_currentTime < MOVING_DURATION) {
        sf::Vector2f pos = GameMath::getMovingEquation(m_currentPos.toPosition(), m_destPos.toPosition(), MOVING_DURATION, m_currentTime);
        float offsetY = GameMath::getHarmonicMotion(40.f, MOVING_DURATION, m_currentTime);
        pos.y += offsetY;
        this->setPosition(pos);
    } else {
        this->setCurrentPosition(m_destPos);
        this->changeState(STATE::IDLE);
        if (m_type != PIECETYPE::PLAYER) {
            this->countTurnLeft();
            DATA->playSound("drop2");
        } else {
            DATA->playSound("drop3");
        }
        this->endTurn();
    }
}

void ChessPiece::handleHurt(float deltaTime) {
    m_currentTime += deltaTime;
    if (m_currentTime < HURT_DURATION) {
        float angle = GameMath::getAngle(m_currentPos.toPosition(), m_shootPos.toPosition());
        float k = GameMath::getHarmonicMotion(HURT_OFFSET, HURT_DURATION, m_currentTime);

        if (k < -HURT_OFFSET/2) this->setColor(HURT_COLOR);
        else this->setColor(m_color);
        float x = 8.f - k * cos(angle);
        float y = 23.f / 2 - k * sin(angle);

        this->setOrigin(sf::Vector2f(x, y));
    } else {
        this->setOrigin(sf::Vector2f(8.f, 23.f / 2));
        changeState(STATE::IDLE);
        this->endTurn();
    }
}

void ChessPiece::handleKill(float deltaTime) {
    m_currentTime += deltaTime;
    if (m_currentTime < HURT_DURATION/2) {
        float angle = GameMath::getAngle(m_currentPos.toPosition(), m_shootPos.toPosition());
        float k = GameMath::getHarmonicMotion(HURT_OFFSET, HURT_DURATION, m_currentTime);

        float x = 8.f - k * cos(angle);
        float y = 23.f / 2 - k * sin(angle);
        this->setOrigin(sf::Vector2f(x, y));

        if (k < -HURT_OFFSET / 2) this->setColor(HURT_COLOR);
    } else if (m_currentTime < KILL_DURATION) {
        sf::Color color = HURT_COLOR;
        color.a = (int)std::max(0.f, (1 - m_currentTime / (KILL_DURATION-HURT_DURATION/2)) * 255);
        this->setColor(color);
    } else {
        changeState(STATE::DEAD);
        this->endTurn();
    }
}

void ChessPiece::setPromotion(bool value) {
    m_isPromotion = value;
}

void ChessPiece::promote(std::string name) {
    if (m_type != PIECETYPE::PAWN || m_isPromotion == false) return;
    //re-construct
    this->m_name = "chess/piece/" + name;
    // set chess piece type
    if (name == "B_King") {
        m_type = PLAYER;
        return;
    }
    name = name.substr(2);
    if (name == "King") m_type = KING;
    else if (name == "Queen") m_type = QUEEN;
    else if (name == "Bishop") m_type = BISHOP;
    else if (name == "Knight") m_type = KNIGHT;
    else if (name == "Rook") m_type = ROOK;
    else m_type = PAWN;
    //re-init
    this->setTexture(*DATA->getTexture(this->m_name));
    m_color = this->getColor();
    m_health = GameRule->getHealthChess(m_type);
    m_queueSize = GameRule->getQueueSizeChess(m_type);
    m_turnLeft = m_queueSize-1;
    //
    m_isPromotion = false;
}