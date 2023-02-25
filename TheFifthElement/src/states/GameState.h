#pragma once
#include <string>
#include <list>
#include "../utils/Manager.h"
#include "../sdlutils/InputHandler.h"

class GameStateMachine;

using namespace std;

class GameState {
protected:
	GameStateMachine* gameStateMachine;
	Manager* mngr_;
public:
	GameState();
	virtual ~GameState();
	virtual void update();
	virtual void render();
	virtual string getStateID() = 0;
};