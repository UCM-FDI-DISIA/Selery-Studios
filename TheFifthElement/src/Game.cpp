#include "Game.h"
Game::Game() {
	SDLUtils::init();
	SDLUtils::instance()->showCursor();
	renderer = SDLUtils::instance()->renderer();
	window = SDLUtils::instance()->window();
	exit = false;
	//GameStateMachine::instance()->pushState(new TopDownState());
	//GameStateMachine::instance()->pushState(new MainMenuState());
	//GameStateMachine::instance()->pushState(new BeatEmUpState(false, "earth"));
	//GameStateMachine::instance()->pushState(new PauseState());
	GameStateMachine::instance()->pushState(new BeatEmUpState());
}

Game::~Game(){ // destructora
	GameStateMachine::instance()->~GameStateMachine();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run(){// bucle de juego
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {// bucle de juego
		SDL_RenderClear(renderer);
		handleEvents();

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			//gameStMc->clearStates(); // elimina estados
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
	//gameStMc->handleEvents();
}

void Game::update(){ //update
	GameManager::instance()->update();
	//gameStMc->update();// actualiza el juego
}

void Game::render() { //render
	GameManager::instance()->render();
	//gameStMc->render();
}

//void Game::refresh() {
//	
//}