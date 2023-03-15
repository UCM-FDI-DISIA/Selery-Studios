#pragma once
#ifndef LIFEEARTHBOSSCOMPONENT_H_
#define LIFEEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "../components/AnimationEarthBossComponent.h"
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

