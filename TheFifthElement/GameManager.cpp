#include "GameManager.h"

GameManager::GameManager() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error cargando SDL";// excepción de SDL
	exit = false;
	//LO DE SOFI
	//gameSTMC=static_cast<GameStateMachine*>(GameStateMachine::Instance())
	gameStMc = new GameStateMachine();
	gameStMc->pushState(new GameState());
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
			render();
			SDL_RenderPresent(renderer);// dibuja en pantalla el estado actual del juego
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