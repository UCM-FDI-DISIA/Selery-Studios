#pragma once
#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H_
#include "Transform.h"
#include "../utils/Vector2D.h"

class MovementComponent : public Component
{
public:

	MovementComponent() {
	
	}
	void initComponent();
	void update();
	void setDir(Vector2D direction) {
		tr->setDir(direction);
	}
private:
	Transform* tr = nullptr;
	
};
#endif