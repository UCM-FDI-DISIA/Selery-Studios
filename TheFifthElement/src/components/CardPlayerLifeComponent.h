#pragma once
#ifndef CARDPLAYERLIFECOMPONENT_H_
#define CARDPLAYERLIFECOMPONENT_H_
#include "../utils/Component.h"

class CardPlayerLifeComponent:public Component
{
private:
	int life;
public:
	CardPlayerLifeComponent(int life_) : life(life_) {}

	void damage(int attack) { life -= attack; }
	int lifeLeft() { return life; }
};
#endif