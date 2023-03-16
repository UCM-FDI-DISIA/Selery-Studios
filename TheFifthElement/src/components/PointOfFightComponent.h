#pragma once
#ifndef POINTOFFIGHTCOMPONENT_H_
#define POINTOFFIGHTCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../components/Transform.h"

class PointOfFightComponent : public Component
{
private:
	Transform* tr_;
	Vector2D pointLeftFight, pointRightFight, center;
	float margin;
public:
	PointOfFightComponent(float margin_);
	virtual ~PointOfFightComponent() {}
	void initComponent();
	void update();
	void render();

	inline Vector2D getPointLeftFight() { return pointLeftFight; }
	inline Vector2D getPointRightFight() { return pointRightFight; }
};
#endif


