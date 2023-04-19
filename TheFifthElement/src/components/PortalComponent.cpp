#include "PortalComponent.h"
#include "../states/TopDownState.h"
PortalComponent::PortalComponent(Transform* trPlayer) {
	trPlayer_ = trPlayer;
	
}
void PortalComponent::initComponent() {
	trPortal = ent_->getComponent<Transform>(TRANSFORM_H);
	portalImage = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	for (int i = 0; i < 4; i++) {
		Entity* obelisk = new Entity();
		obelisk->setContext(mngr_);
		Vector2D pos = trPortal->getPos();
		if (i == 0) {
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(OBELISK_WIDTH * (-1), trPortal->getH() / 2 - 20), OBELISK_WIDTH, OBELISK_HEIGHT);
			obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("ObeliskAir"), OBELISK_WIDTH, OBELISK_HEIGHT, 16);
		}
		else if (i == 1) {
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(trPortal->getW() / 4 - OBELISK_WIDTH, -20), OBELISK_WIDTH, OBELISK_HEIGHT);
			obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("ObeliskFire"), OBELISK_WIDTH, OBELISK_HEIGHT, 16);
		}
		else if (i == 2) {
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(trPortal->getW() / (4.0 / 3.0), -20), OBELISK_WIDTH, OBELISK_HEIGHT);
			obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("ObeliskEarth"), OBELISK_WIDTH, OBELISK_HEIGHT, 16);
		}
		else if (i == 3) {
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(trPortal->getW(), trPortal->getH() / 2 - 20), OBELISK_WIDTH, OBELISK_HEIGHT);
			obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("ObeliskWater"), OBELISK_WIDTH, OBELISK_HEIGHT, 16);
		}
		
		mngr_->addEntity(obelisk);
	}
}

void PortalComponent::update() {

}

void PortalComponent::elementEarned() {
	//ent_->addComponent<CheckCollision>(CHECKCOLLISION_H, static_cast<TopDownState*> (mngr_)->getplayer(), "portal");
	if (Elements::instance()->getAir() && Elements::instance()->getEarth() && Elements::instance()->getFire() && Elements::instance()->getWater()) {
		ent_->addComponent<CheckCollision>(CHECKCOLLISION_H, static_cast<TopDownState*> (mngr_)->getplayer(), "portal");
		
	}
}

void PortalComponent::Teleport(Vector2D newPlayerPos) {
	trPlayer_->setPos(newPlayerPos);
}