#pragma once
#include "utils/checkML.h"
#include "states/GameStateMachine.h"
#include "sdlutils/SDLUtils.h"
using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;// anchura de ventana
const uint WIN_HEIGHT = 900;// altura de ventana
const uint FRAME_RATE = 3;// número de frames que tardará en actualizarse el juego


class GameManager:public Singleton <GameManager>
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStMc;
	bool exit;
	double width, height;;

public:
	GameManager() ;
	virtual ~GameManager();
	void handleEvents();
	inline double getWindowWidth() { return width; };
	inline double getWindowHeight() { return height; };
	void render();
	void update();
	void run();// blucle de juego
	SDL_Renderer* getRenderer() {
		return SDLUtils::instance()->renderer();

	}
};
