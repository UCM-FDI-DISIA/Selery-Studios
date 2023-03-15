#pragma once
#include "MovementComponent.h"
#include "../utils/Entity.h"
using namespace std;
cmpId_type z = int(TRANSFORM_H);

void MovementComponent::initComponent() {
	tr_ = ent_->getComponent<Transform>(z);
}

void MovementComponent::update() {
	tr_->setPos(tr_->getPos() + tr_->getDir() * PLAYERTD_SPEED);
}