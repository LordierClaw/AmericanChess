#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine::GameStateMachine() {
    m_ActiveState = nullptr;
    m_NextState = nullptr;
}

GameStateMachine::~GameStateMachine() {
    while (m_StateStack.size()) {
        delete m_StateStack.back();
        m_StateStack.pop_back();
    }
    m_StateStack.clear();
}

void GameStateMachine::changeState(GameStateBase* state) {
    m_NextState = state;
}

void GameStateMachine::changeState(StateTypes state) {
    GameStateBase* gameState = GameStateBase::createState(state);
    changeState(gameState);
}

void GameStateMachine::pushState(StateTypes state) {
    GameStateBase* gameState = GameStateBase::createState(state);
    if (!m_StateStack.empty()) m_StateStack.back()->pause();
    m_NextState = gameState;
}

void GameStateMachine::popState() {
    if (!m_StateStack.empty()) {
        m_StateStack.back()->exit();
        m_StateStack.pop_back();
    }
    if (!m_StateStack.empty()) {
        m_StateStack.back()->resume();
    }
}

void GameStateMachine::performSateChange() {
    if (m_NextState != nullptr) {
        if (!m_StateStack.empty()) m_StateStack.back()->exit();
        m_StateStack.push_back(m_NextState);
        m_StateStack.back()->init();
        m_ActiveState = m_NextState;
        m_NextState = nullptr;
    }
}

GameStateBase* GameStateMachine::currentState() const {
    return m_ActiveState;
}

GameStateBase* GameStateMachine::nextState() const {
    return m_NextState;
}

bool GameStateMachine::needToChangeState() {
    return m_NextState != nullptr;
}

bool GameStateMachine::hasState() {
    return !m_StateStack.empty();
}
