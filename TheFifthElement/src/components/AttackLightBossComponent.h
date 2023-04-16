#pragma once
#ifndef ATTACKLIGHTBOSSCOMPONENT_H_
#define ATTACKLIGHTBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "Transform.h"
#include "FramedImage.h"

class AttackLightBossComponent: public Component
{
private:
	int fightState;
public:
	AttackLightBossComponent();
	void initComponent();
	void setState(int state);
};

#endif