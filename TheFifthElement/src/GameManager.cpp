#include "GameManager.h"
#include "states/TopDownState.h"
#include "states/BeatEmUpState.h"
#include "states/PauseMenuState.h"
	////LO DE SOFI
	////gameSTMC=static_cast<GameStateMachine*>(GameStateMachine::Instance())
	//gameStMc = new GameStateMachine();

	////Audio de prueba
	////SDLUtils::instance()->soundEffects().at("prueba").play();
	//gameStMc->pushState(new TopDownState());
	////gameStMc->pushState(new BeatEmUpState(this));

void GameManager::goBeatEmUp() {
	SDLUtils::instance()->soundEffects().at("Title").haltChannel();
	GameStateMachine::instance()->pushState(new BeatEmUpState());
}

void GameManager::goTopDown() {
	GameStateMachine::instance()->popState();
	cout << "asasaa";
}

void GameManager:: leaveMainMenu() {
	SDLUtils::instance()->soundEffects().at("Menu").haltChannel();
	GameStateMachine::instance()->pushState(new TopDownState());

}

void GameManager::goPauseMenu() {
	GameStateMachine::instance()->pushState(new PauseMenuState());
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