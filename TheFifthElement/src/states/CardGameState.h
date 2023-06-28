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
#include "../components/DeckManagerComponent.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components//Image.h"
#include "../sdlutils/Font.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/IADeckComponent.h"

//struct cartas: textura reverso, textura anverso, energia, vida y ataque
typedef struct CardsInfo
{
	string anverseName;
	int energy, life, attack, element;
	SDL_Rect place;
	Texture* reverse;
};

class CardGameState: public Manager
{
private:
	SDL_Rect initialPlace = { 0,0,0,0 };
	Texture* generalreverse= &SDLUtils::instance()->images().at("reversoCarta");
	vector<CardsInfo*> playerCards; //pool de las cartas que puede tener solo el player
	vector<CardsInfo*> IACards; //pool de las cartas que puede tener solo la IA
	vector<CardsInfo*> commonCards; //pool de las cartas que pueden tener ambos
	vector<Entity*>playersTurn;
	int numRonda;
	int numTurno;
	int turnTimer;
	Texture* table;
	Texture* energyTex;
	SDL_Rect backRect = {0,0,WIN_WIDTH,WIN_HEIGHT};
	Entity* player;
	DeckManagerComponent* playerDeck;
	Entity* IA;
	IADeckComponent* IADeck;
	Font* font;
	SDL_Color colorFont = { 50,50,0 };
	GameManager* Gm_;
	Texture* playerTurn= &SDLUtils::instance()->images().at("sliderPlayer");
	Texture* IATurn = &SDLUtils::instance()->images().at("sliderIA");
	SDL_Rect sliderRect = { 130,560,100,50 };

public:
	CardGameState();

	virtual void update();
	virtual void render();
	virtual void handleEvents();
	virtual string getStateID() { return "CardsGame"; };
	void nextTurn();
	void deal();
};

