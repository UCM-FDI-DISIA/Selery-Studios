#pragma once
#ifndef PROTECTIONEARTHBOSSCOMPONENT_H_
#define PROTECTIONEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "Image.h"
#include "AnimationEarthBossComponent.h"
#include "MovementEarthBossComponent.h"

class ProtectionEarthBossComponent : public Component
{
private:
	MovementEarthBossComponent* bossMovement;
	AnimationEarthBossComponent* animator;
	float timeExecution, lastProtectionTime, startProtectionTime;
	int intervalProtection;
public:
	ProtectionEarthBossComponent();
	virtual ~ProtectionEarthBossComponent() {}
	void initComponent();
	void update();
	void protect();
	void unprotect();
};
#endif

