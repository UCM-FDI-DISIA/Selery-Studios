#pragma once
#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H_
#include "Transform.h"
#include "utils/Vector2D.h"

class MovementComponent : public Component
{
public:

	MovementComponent();
	void initComponent();
	void update();
private:
	Transform* tr = nullptr; 
	Vector2D speed =Vector2D(0,1);
};
#endif