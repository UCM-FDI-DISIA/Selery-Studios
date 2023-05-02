#include "ObjectsComponent.h"
#include "../states/BeatEmUpState.h"
void ObjectsComponent::initComponent() {
	trPlayer = static_cast<BeatEmUpState*>(mngr_)->getPlayer()->getComponent<Transform>(TRANSFORM_H);
	trObject = ent_->getComponent<Transform>(TRANSFORM_H);
}
void ObjectsComponent::update() {
	Vector2D trPos = Vector2D(trPlayer->getPos().getX(), trPlayer->getPos().getY());
	if (Collision::collides(trObject->getPos(), trObject->getW(), trObject->getH(), trPos, trPlayer->getW() * trPlayer->getS(), trPlayer->getH() * trPlayer->getS())) {
		inRange = true;
	}
	else {
		inRange = false;
	}
}