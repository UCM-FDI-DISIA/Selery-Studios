#include "GameStateMachine.h"
#include "GameState.h"
#include "MainMenuState.h"

GameState::GameState() {
	gameStMc = static_cast<GameStateMachine*>(GameStateMachine::instance());
}

void GameState::render() {
	for (auto e : ents_) e->render();
};

GameState::~GameState() // destructora
{
	for (auto e : ents_) {
		delete e;
	}
}

void GameState::menuToPlay() // ir a juego
{
	
}
