#include "GameManager.h"
#include "states/TopDownState.h"
GameManager::GameManager() {
	SDLUtils::init();
	renderer = SDLUtils::instance()->renderer();
	window = SDLUtils::instance()->window();
	exit = false;
	//LO DE SOFI
	//gameSTMC=static_cast<GameStateMachine*>(GameStateMachine::Instance())
	gameStMc = new GameStateMachine();

	SDLUtils::instance()->soundEffects().at("prueba").play();
	gameStMc->pushState(new TopDownState(this));
}


GameManager::~GameManager()// destructora
{
	delete(gameStMc);// destruye game State Machine
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameManager::run()// bucle de juego
{
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) // bucle de juego
	{
		SDL_RenderClear(renderer);

		handleEvents();

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE)
		{
			update();

			gameStMc->clearStates(); // elimina estados
			startTime = SDL_GetTicks();
		}
		if (!exit)
		{
			SDL_RenderClear(renderer);
			render();
			SDL_RenderPresent(renderer);// dibuja en pantalla el estado actual del juego
			SDL_Delay(10);
		}
	}
}

void GameManager::handleEvents() {
	// handleEvents
	gameStMc->handleEvents();
}

void GameManager::update()
{
	//update
	gameStMc->update();// actualiza el juego
}

void GameManager::render() {
	//render
	gameStMc->render();
}