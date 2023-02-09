#pragma once
#include "utils/Manager.h"
#include "SDL.h" 
#include "utils/checkML.h"
#include "GameStateMachine.h"
#include "GameState.h"
//#include "SDL_error.h"
using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;// anchura de ventana
const uint WIN_HEIGHT = 900;// altura de ventana
const uint FRAME_RATE = 3;// número de frames que tardará en actualizarse el juego


class GameManager  :
	public Manager
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStMc;

public:
	GameManager();
	~GameManager();
	void handleEvents();
	void render();
	void update();
	void run();// blucle de juego
};
