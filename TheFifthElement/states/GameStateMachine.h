#pragma once
#include "../utils/Manager.h"
#include <stack>
#include "GameState.h"

class GameStateMachine :public Manager {
private:
	stack<GameState*> st; // pila de estados
	stack<GameState*> stToDelete; // pila de estados a borrar
public:
	~GameStateMachine(); // destructora
	GameState* currentState(); // acceso al estado actual
	void pushState(GameState* myState); // push de un estado de juego
	void changeState(GameState* myState); // cambio de estado de juego
	void popState(); // pop de estado de juego
	void clearStates(); // borrado de pila "stToDelete"
	void handleEvents();
	void update();
	void render();
};

