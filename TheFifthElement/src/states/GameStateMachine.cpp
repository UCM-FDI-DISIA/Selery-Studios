#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() { // destructora
	while (!st.empty()) {
		stToDelete.push(st.top());
		st.pop();
	}
	clearStates();
}

Manager* GameStateMachine::currentState() { // consulta del estado actual
	return st.top();
}

void GameStateMachine::pushState(Manager* myState) { // push del nuevo estado y entra en él 
	st.push(myState);
}

void GameStateMachine::changeState(Manager* myState) { // cambio de estado
	if (currentState()->getStateID() != myState->getStateID()) {
		popState();
		pushState(myState);
	}
}

Manager* GameStateMachine::state() {
	return st.top();
}

void GameStateMachine::popState() { // pop si la pila no está vacía y salida del estado
	if (!st.empty()) {
		stToDelete.push(st.top());
		st.pop();
	}
}

void GameStateMachine::clearStates() {
	while (!stToDelete.empty()) {
		delete(stToDelete.top());
		stToDelete.pop();
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