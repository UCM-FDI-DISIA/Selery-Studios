#pragma once
#include <string>
#include <list>
//#include "GameStateMachine.h"
#include "utils/Entity.h"
using namespace std;

class GameStateMachine;
class GameState;
class MainMenuState;

class StateManager
{
protected:
	GameStateMachine* gameStMc; 
	list <Entity*> gameObjectList; // lista de gameObjects
public:
	StateManager();
	virtual ~StateManager(); // destructora
	virtual void update() {};
	virtual void render() {};
	virtual void handleEvents() {};
	virtual string getStateID() { return "nothing"; }; // virtual de stringID de cada estado

	// BOTONES
	static void menuToPlay(); // ir al juego
};

