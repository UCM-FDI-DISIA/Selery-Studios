#pragma once
#ifndef MOVEMENTLIGHTBOSSCOMPONENT_H_
#define MOVEMENTLIGHTBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "Transform.h"

class MovementLightBossComponent: public Component
{
private:
	Entity* player_;
	Transform* playerTrans;
	Transform* bossTrans;
	Vector2D newPosRight{ 600,200 };
	Vector2D newPosLeft{ 100,200 };
	float closeX=100;
	float closeY=100;
	float negCloseX = -100;
	float negCloseY = -100;
public:
	MovementLightBossComponent(Entity* player);
	void initComponent();
	void update();

	virtual ~MovementLightBossComponent() {};
};

#endif