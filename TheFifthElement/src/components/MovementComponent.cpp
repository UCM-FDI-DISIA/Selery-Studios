#pragma once
#include "MovementComponent.h"
#include "../utils/Entity.h"
using namespace std;
cmpId_type z = int(TRANSFORM_H);

void MovementComponent::initComponent() {
	tr = ent_->getComponent<Transform>(z);

}

void MovementComponent::update() {
	tr->setPos(tr->getPos() + tr->getVel());

}