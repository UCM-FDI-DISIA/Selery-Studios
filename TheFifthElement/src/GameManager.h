#pragma once
#include "utils/checkML.h"
#include "states/GameStateMachine.h"
#include "sdlutils/SDLUtils.h"
using namespace std;

class GameManager : public Singleton<GameManager>
{
private:
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
		return SDLUtils::instance()->renderer();
	}
	SDL_Window* getWindow() { return window; }

	void goBeatEmUp();
};
