#pragma once
#include "utils/checkML.h"
#include "states/GameStateMachine.h"
#include "sdlutils/SDLUtils.h"
using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;// anchura de ventana
const uint WIN_HEIGHT = 900;// altura de ventana
const uint FRAME_RATE = 3;// número de frames que tardará en actualizarse el juego


class GameManager : public Singleton<GameManager>
{
private:
	bool exit;
public:
	void handleEvents();
	void render();
	void update();
	SDL_Renderer* getRenderer() {
		return SDLUtils::instance()->renderer();
	}
	SDL_Window* getWindow() { return SDLUtils::instance()->window(); }

	void goBeatEmUp();
	void goTopDown();
};
