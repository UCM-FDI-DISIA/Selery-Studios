#pragma once
#include "../utils/Singleton.h"
#include <stack>
#include "../utils/Manager.h"

class GameStateMachine: public Singleton <GameStateMachine> {
private:
	stack<Manager*> st; // pila de escenas
	stack<Manager*> stToDelete; // pila de escenas a borrar
public:
	~GameStateMachine(); // destructora
	Manager* currentState(); // acceso al estado actual
	void pushState(Manager* myState); // push de un estado de juego
	void changeState(Manager* myState); // cambio de estado de juego
	void popState(); // pop de estado de juego
	void clearStates(); // borrado de pila "stToDelete"
	void handleEvents();
	void update();
	void render();
};

