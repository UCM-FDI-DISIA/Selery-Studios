#pragma once
#ifndef MOVEMENTEARTHBOSSCOMPONENT_H_
#define MOVEMENTEARTHBOSSCOMPONENT_H_
#include "src/utils/Vector2D.h"
#include "src/utils/Component.h"
#include "src/components/Transform.h"

class MovementEarthBossComponent : public Component
{
private:
	Transform* playerTransform;
	Transform* bossTransform;
public:
	MovementEarthBossComponent(Transform* tr);
	virtual ~MovementEarthBossComponent() {}
	void initComponent();
	void update();
};
#endif

