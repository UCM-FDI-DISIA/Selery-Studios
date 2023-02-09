#pragma once
#include "utils/Manager.h"
#include <stack>
#include "StateManager.h"

class GameStateMachine :
    public Manager
{
private:
	stack<StateManager*> st; // pila de estados
	stack<StateManager*> stToDelete; // pila de estados a borrar
public:
	~GameStateMachine(); // destructora
	StateManager* currentState(); // acceso al estado actual
	void pushState(StateManager* myState); // push de un estado de juego
	void changeState(StateManager* myState); // cambio de estado de juego
	void popState(); // pop de estado de juego
	void clearStates(); // borrado de pila "stToDelete"
	void handleEvents();
	void update();
	void render();
};

