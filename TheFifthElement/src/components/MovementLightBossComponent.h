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
	Vector2D movDir;

public:
	MovementLightBossComponent(Entity* player);
	void initComponent();
	void update();
	void teleport();
	void move(Vector2D dir);
	virtual ~MovementLightBossComponent() {};
};

#endif