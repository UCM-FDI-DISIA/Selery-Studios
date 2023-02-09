#include "StateManager.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "MainMenuState.h"


StateManager::StateManager() {
	gameStMc = static_cast<GameStateMachine*>(GameStateMachine::instance());
}


StateManager::~StateManager() // destructora
{
	for (list<Entity*>::iterator it = gameObjectList.begin(); it != gameObjectList.end();)
	{
		++it;
		delete(*gameObjectList.begin());
		gameObjectList.pop_front();
	}
}

void StateManager::menuToPlay() // ir a juego
{
	
}
