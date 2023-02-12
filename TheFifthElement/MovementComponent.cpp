#pragma once
#include "MovementComponent.h"
#include "utils/Entity.h"
cmpId_type z = int(_TRANSFORM_H_);

MovementComponent::MovementComponent() {
	tr = ent_->getComponent<Transform>(z);
}

void MovementComponent::update() {
	tr->setPos(tr->getPos() + speed);
}