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
	float margin, height; // Margen a los lados y altura a la que estan dichos puntos de combate
public:
	PointOfFightComponent(float margin_, float height_);
	virtual ~PointOfFightComponent() {}
	void initComponent();
	void update();
	void render();

	inline Vector2D getPointLeftFight() { return pointLeftFight; }
	inline Vector2D getPointRightFight() { return pointRightFight; }
};
#endif


