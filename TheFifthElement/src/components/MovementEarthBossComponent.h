#pragma once
#ifndef MOVEMENTEARTHBOSSCOMPONENT_H_
#define MOVEMENTEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../components/Transform.h"

class MovementEarthBossComponent : public Component
{
private:
	Transform* playerTransform;
	Transform* bossTransform;
	Vector2D pointLeftFight, pointRightFight;
public:
	MovementEarthBossComponent(Transform* tr);
	virtual ~MovementEarthBossComponent() {}
	void initComponent();
	void update();
	void render();
};
#endif

