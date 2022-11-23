#include "GameStateBase.h"
#include "State/GSIntro.h"
#include "State/GSMenu.h"
#include "State/GSAbout.h"
#include "State/GSPlay.h"
#include "State/GSModeSelect.h"
#include "State/GSUpgrade.h"
#include "State/GSEnd.h"

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
	case MODESELECT:
		gameState = new GSModeSelect();
		break;
	case UPGRADE:
		gameState = new GSUpgrade();
		break;
	case END:
		gameState = new GSEnd();
		break;
	default:
		break;
	}
	return gameState;
}
