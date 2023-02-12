#pragma once
#include "Transform.h"
#include "utils/Vector2D.h"
#include "utils/Entity.h"

class MovementComponent : Component
{
public:

	MovementComponent();
	void update();
private:
	Transform* tr = nullptr; Vector2D speed;
};