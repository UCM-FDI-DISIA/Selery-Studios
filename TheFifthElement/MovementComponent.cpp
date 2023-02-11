#include "MovementComponent.h"


MovementComponent::MovementComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM_H_);
}

void MovementComponent::update() {
	tr->setPos(tr->getPos() + speed);
}