#pragma once
#include "utils/checkML.h"
#include "states/GameStateMachine.h"
#include "sdlutils/SDLUtils.h"
using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;// anchura de ventana
const uint WIN_HEIGHT = 900;// altura de ventana
const uint FRAME_RATE = 3;// n�mero de frames que tardar� en actualizarse el juego


class GameManager:public Singleton <GameManager>
{
private:
	SDLUtils* sdl_utils = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStMc;
	bool exit;

public:
	GameManager() ;
	virtual ~GameManager();
	void handleEvents();
	void render();
	void update();
	void run();// blucle de juego
	SDL_Renderer* getRenderer() {
		return sdl_utils->renderer();
	}
};
