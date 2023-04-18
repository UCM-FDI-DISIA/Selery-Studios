#pragma once
#include <string>
#include <list>
#include "../utils/Manager.h"
using namespace std;

class GameState: public Manager{
protected:
	//puntero a la maquina de estados
public:
	GameState();
	virtual ~GameState(); // destructora
	virtual void update();
	virtual void render();
	virtual void handleEvents();
	virtual string getStateID() { return "nothing"; }; // virtual de stringID de cada 
	static void menuToPlay(); // ir al juego
};