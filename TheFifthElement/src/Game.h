#pragma once
#include "sdlutils/SDLUtils.h"
#include "utils/checkML.h"
#include "states/GameStateMachine.h"
#include "GameManager.h"
#include "states/TopDownState.h"
#include "states/BeatEmUpState.h"
#include "states/MainMenuState.h"
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

