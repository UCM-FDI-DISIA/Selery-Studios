#include "GameStateMachine.h"
#include "GameState.h"

GameState::GameState() {

}

GameState::~GameState() { // destructora
	for (auto e : ents_) {
		delete e;
	}
}

void GameState::update() {
	for (auto e : ents_) e->update();
}

void GameState::render() {
	for (auto e : ents_) e->render();
};

void GameState::handleEvents() {
	Manager::handleEvents();
}