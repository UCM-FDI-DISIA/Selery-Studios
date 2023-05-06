#include "Game.h"

Game::Game() {
	SDLUtils::init();
	sdlutils().showCursor();
	renderer = sdlutils().renderer();
	window = sdlutils().window();
	exit = false;
	Elements::instance();
	GameManager::instance()->setGame(this);

	GameStateMachine::instance()->pushState(new MainMenuState());
}

Game::~Game(){ // destructora
	GameStateMachine::instance()->~GameStateMachine();

	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	SDL_DestroyWindow(window);
	
}

void Game::run(){// bucle de juego
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {// bucle de juego
		handleEvents();

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			refresh();
			GameStateMachine::instance()->clearStates(); // elimina estados
			startTime = SDL_GetTicks();
		}
		SDL_RenderClear(renderer);
		render();
		SDL_RenderPresent(renderer);// dibuja en pantalla el estado actual del juego
		SDL_Delay(10);
	}
}

void Game::handleEvents() { // handleEvents
	GameManager::instance()->handleEvents();
}

void Game::update(){ //update
	GameManager::instance()->update();
}

void Game::render() { //render
	GameManager::instance()->render();
}

void Game::refresh() {
	GameStateMachine::instance()->currentState()->refresh();
}