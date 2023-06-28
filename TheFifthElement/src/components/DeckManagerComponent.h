#pragma once
#ifndef DECKMANAGERCOMPONENT_H_
#define DECKMANAGERCOMPONENT_H_
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "../GameManager.h"
#include <vector>
#include "../sdlutils/Font.h"

struct CardsInfo;

class DeckManagerComponent:public Component
{
private:
	Entity* player;
	vector<CardsInfo*> deck;
	vector<CardsInfo*> hand;
	vector<CardsInfo*> table;
	int energy;
	Font* font;
	SDL_Rect endTurnButtonRect = { 130,560,100,50 };
public:
	DeckManagerComponent(Entity* player_) :player(player_) {font= &SDLUtils::instance()->fonts().at("TCenturyScale");}

	void shuffleDeck(CardsInfo* card) { deck.push_back(card); }
	void drawCard(int numCards);
	void endTurn();
	void render();
	void receiveEnergy(int qty) {energy = qty;}
	int getEnergy() { return energy; }
	void handleEvents(SDL_Event event);
};
#endif