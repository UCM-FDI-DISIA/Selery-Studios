#pragma once
#ifndef ATTACKEARTHBOSSCOMPONENT_H_
#define ATTACKEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "Image.h"
#include "MovementEarthBossComponent.h"

class AttackEarthBossComponent : public Component
{
private:
	Image* imBoss;
	MovementEarthBossComponent* bossMovement;
	AnimationEarthBossComponent* animator;
public:
	AttackEarthBossComponent();
	virtual ~AttackEarthBossComponent() {}
	void initComponent();
	void update();
};
#endif
