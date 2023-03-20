#pragma once
#ifndef LIFEEARTHBOSSCOMPONENT_H_
#define LIFEEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "AnimationEarthBossComponent.h"
#include "ObjectsComponent.h"
class LifeEarthBossComponent : public Component
{
private:
	AnimationEarthBossComponent* animEarthBoss;
	Image* bossImage;
	Transform* bossTransform;
	int life, maxLife, stage = 1;
public:
	LifeEarthBossComponent();
	virtual ~LifeEarthBossComponent() {}
	void receiveDamage(float damage, float mul);
	void initComponent();
	void stageTwo();
};
#endif

