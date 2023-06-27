#pragma once
#ifndef IADECKCOMPONENT_H_
#define IADECKCOMPONENT_H_
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "../GameManager.h"


class IADeckComponent :public Component
{
private:
	Entity* IA;
	Entity* enemy;
	//debo tener 3 pilas de cartas: baraja, mano y mesa
	int energy;
public:
	IADeckComponent(Entity* IA_, Entity* enemy_) :IA(IA_),enemy(enemy_) {}

	void drawCard(int numCards);
	void endTurn();
	void render() {}
	void receiveEnergy(int qty) { energy = qty; }
	int getEnergy() { return energy; }
};
#endif