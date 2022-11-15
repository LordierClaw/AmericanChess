#include "GameStateBase.h"
#include "State/GSIntro.h"
#include "State/GSMenu.h"
#include "State/GSPlay.h"
#include "State/GSAbout.h"

GameStateBase* GameStateBase::createState(StateTypes state) {
	GameStateBase* gameState = nullptr;
	switch (state) {
	case INVALID:
		break;
	case INTRO:
		gameState = new GSIntro();
		break;
	case MENU:
		gameState = new GSMenu();
		break;
	case ABOUT:
		gameState = new GSAbout();
		break;
	case PLAY:
		gameState = new GSPlay();
		break;
	case UPGRADE:
		break;
	case END:
		break;
	default:
		break;
	}
	return gameState;
}
