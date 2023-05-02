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
	float extraDamage = 0;
public:
	AttackEarthBossComponent();
	virtual ~AttackEarthBossComponent() {}
	void initComponent();
	void update();

	inline float getExtraDamage() { return extraDamage; }
	inline void setExtraDamage(int newValue) { extraDamage = newValue; }
	inline void addExtraDamage() { extraDamage += 0.1; }
};
#endif
