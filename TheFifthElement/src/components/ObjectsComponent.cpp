#include "ObjectsComponent.h"
#include "../states/BeatEmUpState.h"
void ObjectsComponent::initComponent() {
	trPlayer = static_cast<BeatEmUpState*>(mngr_)->getPlayer()->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
	trObject = ent_->getComponent<Transform>(TRANSFORM_H);
}
void ObjectsComponent::update() {
	Vector2D trPos = Vector2D(trPlayer->getColRect().x, trPlayer->getColRect().y);
	if (Collision::collides(trObject->getPos(), trObject->getW(), trObject->getH(), trPos, trPlayer->getColRect().w, trPlayer->getColRect().h)) {
		inRange = true;
	}
	else {
		inRange = false;
	}
}