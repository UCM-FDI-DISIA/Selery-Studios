#pragma once
<<<<<<< Updated upstream
#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H_
#include "Transform.h"
#include "utils/Vector2D.h"

class MovementComponent : Component
{
public:

	MovementComponent();
	void update();
private:
	Transform* tr = nullptr; Vector2D speed;
};
#endif
=======
#include "Transform.h"
#include "utils/Component.h"
#include "utils/Vector2D.h"

class MovementComponent : public Component
{
public:
	MovementComponent(Transform* tr_);
	void update();
private:
	Transform* tr = nullptr;
	Vector2D speed;
};
>>>>>>> Stashed changes
