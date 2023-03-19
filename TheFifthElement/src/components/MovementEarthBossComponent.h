#pragma once
#ifndef MOVEMENTEARTHBOSSCOMPONENT_H_
#define MOVEMENTEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../components/Transform.h"
#include "../components/PointOfFightComponent.h"

class MovementEarthBossComponent : public Component
{
private:
	Transform* playerTransform;
	Transform* bossTransform;
	PointOfFightComponent* fightPlayerComp;
	Entity* player_;
public:
	MovementEarthBossComponent(Entity* player);
	virtual ~MovementEarthBossComponent() {}
	void initComponent();
	void update();
};
#endif

