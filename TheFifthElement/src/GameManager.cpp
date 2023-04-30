#include "GameManager.h"
#include "states/MainMenuState.h"
#include "states/TopDownState.h"
#include "states/BeatEmUpState.h"
#include "states/PauseState.h"
#include "Game.h"

	////Audio de prueba
	////SDLUtils::instance()->soundEffects().at("prueba").play();
	//gameStMc->pushState(new TopDownState());
	////gameStMc->pushState(new BeatEmUpState(this));

void GameManager::goBeatEmUp(bool boss, Entity* enemy, string typeboss) {
	SDLUtils::instance()->soundEffects().at("Title").haltChannel();
	GameStateMachine::instance()->pushState(new BeatEmUpState(boss, enemy, typeboss));
}

void GameManager::goTopDown() {
	SDLUtils::instance()->soundEffects().at("Title").play();
	GameStateMachine::instance()->popState();
}
void GameManager::goToEndState() {
	GameStateMachine::instance()->changeState(new EndState());
}

void GameManager::backToMainMenu() {
	SDLUtils::instance()->soundEffects().at("Title").haltChannel();
	GameStateMachine::instance()->changeState(new MainMenuState());
}
void GameManager::LoadGame() {
	GameStateMachine::instance()->pushState(new TopDownState(true));
}
void GameManager:: leaveMainMenu() {
	GameStateMachine::instance()->pushState(new TopDownState(false));
	//GameStateMachine::instance()->pushState(new BeatEmUpState(false));
}

void GameManager::goPauseMenu() {
	GameStateMachine::instance()->pushState(new PauseState());
}

void GameManager::goOptionsMenu() {
	GameStateMachine::instance()->pushState(new OptionsState());
}

void GameManager::Pop() {
	GameStateMachine::instance()->popState();
}

void GameManager::handleEvents() { // handleEvents
	GameStateMachine::instance()->handleEvents();
}

void GameManager::update() { //update
	GameStateMachine::instance()->update();// actualiza el juego
	/*GameStateMachine::instance()->clearStates();*/
}

void GameManager::render() { //render
	GameStateMachine::instance()->render();
}
