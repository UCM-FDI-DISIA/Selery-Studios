#pragma once
#include "utils/checkML.h"
#include "states/GameStateMachine.h"
#include "sdlutils/SDLUtils.h"
using namespace std;

using uint = unsigned int;

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
	void leaveMainMenu();
	static void goPauseMenu();
	static void backToMainMenu();

};
