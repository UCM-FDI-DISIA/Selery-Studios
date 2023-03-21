#include "GameManager.h"
#include "states/MainMenuState.h"
#include "states/TopDownState.h"
#include "states/BeatEmUpState.h"
#include "states/PauseState.h"
	////LO DE SOFI
	////gameSTMC=static_cast<GameStateMachine*>(GameStateMachine::Instance())
	//gameStMc = new GameStateMachine();

	////Audio de prueba
	////SDLUtils::instance()->soundEffects().at("prueba").play();
	//gameStMc->pushState(new TopDownState());
	////gameStMc->pushState(new BeatEmUpState(this));

void GameManager::goBeatEmUp() {
	SDLUtils::instance()->soundEffects().at("Title").haltChannel();
	GameStateMachine::instance()->pushState(new BeatEmUpState(false));
}

void GameManager::goTopDown() {
	GameStateMachine::instance()->popState();
}

void GameManager::backToMainMenu() {
	GameStateMachine::instance()->changeState(new MainMenuState());
}

void GameManager:: leaveMainMenu() {
	GameStateMachine::instance()->pushState(new TopDownState());
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
	GameStateMachine::instance()->clearStates();
}

void GameManager::render() { //render
	GameStateMachine::instance()->render();
}
