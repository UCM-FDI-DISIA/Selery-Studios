#pragma once
#include "MovementComponent.h"
#include "../utils/Entity.h"
using namespace std;

void MovementComponent::initComponent() {
	tr = ent_->getComponent<Transform>(TRANSFORM_H);
}

void MovementComponent::update() {
	tr->setPos(tr->getPos() + tr->getDir() * tr->getVel());
}