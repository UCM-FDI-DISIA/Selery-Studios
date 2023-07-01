#pragma once
#ifndef CARDPLAYERLIFECOMPONENT_H_
#define CARDPLAYERLIFECOMPONENT_H_
#include "../utils/Component.h"
#include <string>

class CardPlayerLifeComponent:public Component
{
private:
	int life;
	string entName;
public:
	CardPlayerLifeComponent(int life_, string name) : life(life_), entName(name) {}

	void damage(int attack);
	int lifeLeft() { return life; }
};
#endif