#pragma once
#ifndef LIFEEARTHBOSSCOMPONENT_H_
#define LIFEEARTHBOSSCOMPONENT_H_
#include "src/utils/Vector2D.h"
#include "src/utils/Component.h"
#include "src/utils/Entity.h"

class LifeEarthBossComponent : public Component
{
private:
	int life, maxLife;
public:
	LifeEarthBossComponent();
	virtual ~LifeEarthBossComponent() {}
	void receiveDamage(float damage, float mul);
};
#endif

