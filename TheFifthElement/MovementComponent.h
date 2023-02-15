#pragma once
#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H_
#include "Transform.h"
#include "utils/Vector2D.h"

class MovementComponent : public Component
{
public:

	MovementComponent(float speed) {
		speed_ = speed;
	}
	void initComponent();
	void update();
	void setDir(Vector2D direction) {
		speed = direction * speed_;
	}
private:
	Transform* tr = nullptr;
	float speed_;
	Vector2D speed;
};
#endif