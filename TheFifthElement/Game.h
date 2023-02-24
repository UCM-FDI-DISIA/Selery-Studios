#pragma once
#include "src/sdlutils/SDLUtils.h"
#include "src/utils/checkML.h"
#include "src/states/GameStateMachine.h"
#include "src/GameManager.h"
#include "src/states/TopDownState.h"
class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit;
public:
	Game();
	virtual ~Game();
	void handleEvents();
	void render();
	void update();
	void run();// blucle de juego
	SDL_Renderer* getRenderer() {
		return SDLUtils::instance()->renderer();
	}
	SDL_Window* getWindow() { return window; }
};

