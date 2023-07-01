#pragma once
#ifndef IADECKCOMPONENT_H_
#define IADECKCOMPONENT_H_
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "../GameManager.h"
#include <vector>
#include "../sdlutils/Font.h"
#include "DeckManagerComponent.h"

struct CardsInfo;

class IADeckComponent :public Component
{
private:
	Entity* IA;
	DeckManagerComponent* enemy;
	//debo tener 3 pilas de cartas: baraja, mano y mesa
	vector<CardsInfo*> deck;
	vector<CardsInfo*> hand;
	vector<CardsInfo*> table;
	int energy;
	Font* font;
	SDL_Rect endTurnButtonRect = { 130,560,100,50 };
	SDL_Rect deckStack = { 1690,210,90,110 };
	SDL_Rect handStack = { 170,140,135,165 };
	SDL_Rect tableStack = { 285,336,135,165 };
	GameManager* Gm_;
	SDL_Color color = { 255,255,255 };
	CardsInfo* selectedHand=nullptr;
	int selectedHandIt, selectedHandEnergy;
	SDL_Rect tablePlace = { 285,313,1320,423 };
	CardsInfo* selectTable = nullptr;

public:
	IADeckComponent(GameManager* Gm, Entity* IA_, DeckManagerComponent* enemy_) :Gm_(Gm), IA(IA_),enemy(enemy_) { font = &SDLUtils::instance()->fonts().at("TCenturyScale"); }

	void shuffleDeck(CardsInfo* card) { deck.push_back(card); }
	void drawCard(int numCards);
	void endTurn();
	void render();
	void receiveEnergy(int qty) { energy = qty; }
	int getEnergy() { return energy; }
	void addTableTurn(); //metodo para comprobar las rondas que lleva cada carta en la mesa
	int deckCardsLeft() { return deck.size(); }
	void playCards();
	void playAttack();
	void reviewCards();
	int tableCardsLeft() { return table.size(); }
	vector<CardsInfo*> getTableCards() { return table; }
	void animateAttack();
};
#endif