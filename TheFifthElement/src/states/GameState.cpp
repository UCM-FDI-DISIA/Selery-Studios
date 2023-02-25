#include "GameStateMachine.h"
#include "GameState.h"

GameState::GameState() {
	gameStateMachine = static_cast<GameStateMachine*>(GameStateMachine::instance());
	mngr_ = Manager::instance();
}

void GameState::render() {
	mngr_->render();
}

GameState::~GameState() {
	mngr_->~Manager();
}

void GameState::update() {
	ih().refresh();
	mngr_->update();
	mngr_->refresh();
}