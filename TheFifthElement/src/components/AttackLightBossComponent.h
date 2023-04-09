#pragma once
#ifndef ATTACKLIGHTBOSSCOMPONENT_H_
#define ATTACKLIGHTBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "Transform.h"
#include "FramedImage.h"
#include "MovementLightBossComponent.h"
#include "MovementComponent.h"
#include "DisableOnExit.h"
#include "ColliderComponent.h"
#include "ColDetectorComponent.h"

class AttackLightBossComponent: public Component
{
private:
	int fightState;
	Entity* player_;
	MovementLightBossComponent* movBoss_;
	Transform* playerTrans;
	Transform* bossTrans;
	float distX, distY;
	float closeX = 200;
	float closeY = 100;
	float negCloseX = -200;
	float negCloseY = -100;
	Vector2D dirAtk;
	Vector2D dirMov;
	int timer;
	int contAtks;
	Transform* arrowTrans_;
	FramedImage* arrowIm_;
public:
	AttackLightBossComponent(Entity* player);
	void initComponent();
	void setState(int state);
	void update();
	void attack1();
	void attack2();
};

#endif