#pragma once
#include "MovementComponent.h"
#include "../utils/Entity.h"
using namespace std;

void MovementComponent::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

void MovementComponent::update() {
	tr_->setPos(tr_->getPos() + tr_->getDir() * PLAYERTD_SPEED);
}

void MovementComponent::setNewPos(Vector2D position)
{
	tr_->setPos(position);
}