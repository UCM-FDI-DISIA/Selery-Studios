#include "GameStateMachine.h"
GameStateMachine::~GameStateMachine() { // destructora
	clearStates();
	while (!st.empty())
	{
		delete(st.top());
		st.pop();
	}
}

Manager* GameStateMachine::currentState() { // consulta del estado actual
	return st.top();
}

void GameStateMachine::pushState(Manager* myState) { // push del nuevo estado y entra en él 
	st.push(myState);
}

void GameStateMachine::changeState(Manager* myState) // cambio de estado
{
	//le pasa el nuevo playState a game para que siempre tenga acceso al último PlayState (es decir el que se está ejecutando)
	//if (myState->getStateID() == "play") game->ChangePlayState(static_cast<PlayState*>(myState)); // cambio de playState de game

	if (currentState()->getStateID() != myState->getStateID()) {
		popState();
		pushState(myState);
	}
}

void GameStateMachine::popState() { // pop si la pila no está vacía y salida del estado
	if (!st.empty()) {
		stToDelete.push(st.top());
		st.pop();
	}
}

void GameStateMachine::clearStates() {
	while (!stToDelete.empty()) {
		delete(stToDelete.top());// elimina estado
		stToDelete.pop();// quita estado de la lista de eliminados
	}
}

void GameStateMachine::handleEvents() {
	currentState()->handleEvents();
}

void GameStateMachine::update() {
	currentState()->update();
}

void GameStateMachine::render() {
	currentState()->render();
}

