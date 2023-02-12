#pragma once
#include "MovementComponent.h"
#include "utils/Entity.h"
cmpId_type z = int(TRANSFORM_H_);

<<<<<<< Updated upstream
MovementComponent::MovementComponent() {
	tr = ent_->getComponent<Transform>(z);
=======
MovementComponent::MovementComponent(Transform* tr_):Component() {
	tr = tr_;
	//tr = ent_->getComponent<Transform>(z);
>>>>>>> Stashed changes
}

void MovementComponent::update() {
	tr->setPos(tr->getPos() + speed);
}