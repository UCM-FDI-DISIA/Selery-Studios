#pragma once
#ifndef LIFEEARTHBOSSCOMPONENT_H_
#define LIFEEARTHBOSSCOMPONENT_H_
#include "src/utils/Vector2D.h"
#include "src/utils/Component.h"
#include "src/utils/Entity.h"
#include "AnimationEarthBossComponent.h"
class LifeEarthBossComponent : public Component
{
private:
	AnimationEarthBossComponent* animEarthBoss;
	int life, maxLife;
public:
	LifeEarthBossComponent();
	virtual ~LifeEarthBossComponent() {}
	void receiveDamage(float damage, float mul);
	void initComponent();
};
#endif

