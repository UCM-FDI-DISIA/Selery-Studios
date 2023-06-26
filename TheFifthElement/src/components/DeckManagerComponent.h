#pragma once
#ifndef DECKMANAGERCOMPONENT_H_
#define DECKMANAGERCOMPONENT_H_
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "../GameManager.h"


class DeckManagerComponent:public Component
{
private:
	Entity* player;
	//debo tener 3 pilas de cartas: baraja, mano y mesa
public:
	DeckManagerComponent(Entity* player_) :player(player_) {}

	void drawCard(int numCards);
	void endTurn();
	void render() {}
};
#endif