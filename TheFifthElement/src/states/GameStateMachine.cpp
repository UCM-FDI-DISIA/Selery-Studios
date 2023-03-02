#include "GameStateMachine.h"
#include "../Game.h"

GameStateMachine::GameStateMachine(Game* Game) {
	game = Game;
}

GameStateMachine::~GameStateMachine() {
	clearStates();
	while (!states.empty()) {
		delete(states.top());
		states.pop();
	}
}



GameState* GameStateMachine::currentState() { // Devuelve estado actual
	return states.top();
}

void GameStateMachine::pushState(GameState* myState) { // Push del nuevo estado
	states.push(myState);
}

void GameStateMachine::changeState(GameState* myState) { // cambio de estado
	if (currentState()->getStateID() != myState->getStateID()) {
		popState();
		pushState(myState);
	}
}

void GameStateMachine::popState() { // pop si la pila no está vacía y salida del estado
<<<<<<< Updated upstream
	if (!states.empty()) {
		statesToDelete.push(states.top());
		states.pop();
=======
	if (!st.empty()) {
		stToDelete.push(st.top());
		st.pop();
>>>>>>> Stashed changes
	}
}

void GameStateMachine::clearStates() {
<<<<<<< Updated upstream
	while (!statesToDelete.empty()) {
		delete(statesToDelete.top());// elimina estado
		statesToDelete.pop();// quita estado de la lista de eliminados
=======
	while (!stToDelete.empty()){
		delete(stToDelete.top());// elimina estado
		stToDelete.pop();// quita estado de la lista de eliminados
>>>>>>> Stashed changes
	}
}

void GameStateMachine::update() {
	currentState()->update();
}

void GameStateMachine::render() {
	currentState()->render();
}

