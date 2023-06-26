#pragma once
#include "../utils/PropertiesManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../include/SDL_mixer.h"
#include "../components/Transform.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "../components/Image.h"
#include "../components/Button.h"
#include <vector>

//struct cartas: textura reverso, textura anverso, energia, vida y ataque
typedef struct
{
	Texture* reverse;
	Texture* anverse;
	int energy, life, attack;
}CardsInfo;

class CardGameState: public Manager
{
private:
	vector<CardsInfo> playerCards = { {},{},{},{},{},{},{},{} };
	vector<CardsInfo> IACards = { {},{},{} };
	vector<CardsInfo> commonCards = { {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{} };
	vector<Entity*>playersTurn;
	int numRonda;
	int numTurno;
	int turnTimer;
	Texture* table;
	SDL_Rect backRect;
public:
	CardGameState();

	virtual void update();
	virtual void render();
	virtual void handleEvents();
	virtual string getStateID() { return "CardsGame"; };
};

