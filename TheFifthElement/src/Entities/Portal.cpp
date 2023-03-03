#include "Portal.h"
Portal::Portal(PlayerTD* player) : Entity()
{
	player_ = player;
	tr = addComponent<Transform>(TRANSFORM_H, portalPosition_, portalWidth_, portalHeight_, portalRotation_, portalVel, nframes, false);
	trPlayer_ = player_->getComponent<Transform>(TRANSFORM_H);
	t = &SDLUtils::instance()->images().at("portal");
	addComponent<Image>(IMAGE_H, t, nframes, nframes, 0, PORTAL_WIDTH, PORTAL_HEIGHT);
	addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
}

void Portal::elementEarned() {
	++elementsCollected;
	cout << "Elemento recogido";
	if (elementsCollected == 3) {
		ch = addComponent<CheckCollision>(CHECKCOLLISION_H, player_, "portal");
	}
}

void Portal::Teleport(Vector2D newPlayerPos) {
	trPlayer_->setPos(newPlayerPos);
}