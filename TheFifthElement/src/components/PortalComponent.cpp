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
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(OBELISK_WIDTH * (WIN_WIDTH / 900) * (-1), trPortal->getH() / 2 - 20), OBELISK_WIDTH, OBELISK_HEIGHT);
			fireObeliskImage = obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("Obelisk"), OBELISK_WIDTH, OBELISK_HEIGHT, 1);
		}
		else if (i == 1) {
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(trPortal->getW() / 4 - OBELISK_WIDTH * (WIN_WIDTH / 900), -20), OBELISK_WIDTH, OBELISK_HEIGHT);
			obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("ObeliskAir"), OBELISK_WIDTH, OBELISK_HEIGHT, 16);
		}
		else if (i == 2) {
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(trPortal->getW() / (4.0 / 3.0), -20), OBELISK_WIDTH, OBELISK_HEIGHT);
			waterObeliskImage = obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("Obelisk"), OBELISK_WIDTH, OBELISK_HEIGHT, 1);
		}
		else if (i == 3) {
			obelisk->addComponent<Transform>(TRANSFORM_H, pos + Vector2D(trPortal->getW(), trPortal->getH() / 2 - 20), OBELISK_WIDTH, OBELISK_HEIGHT);
			earthObeliskImage = obelisk->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("Obelisk"), OBELISK_WIDTH, OBELISK_HEIGHT, 1);
		}
		
		mngr_->addEntity(obelisk);
	}
}

void PortalComponent::update() {
	if (!setFire && Elements::instance()->getFire()) {
		fireObeliskImage->setAnim("ObeliskFire", 16, true);
		setFire = true;
	}
	if (!setWater && Elements::instance()->getWater()) {
		waterObeliskImage->setAnim("ObeliskWater", 16, true);
		setWater = true;
	}
	if (!setEarth && Elements::instance()->getEarth()) {
		earthObeliskImage->setAnim("ObeliskEarth", 16, true);
		setEarth = true;
	}
	if (!setCheckCollision && Elements::instance()->getAir() && Elements::instance()->getEarth() && Elements::instance()->getFire() && Elements::instance()->getWater()) {
		ent_->addComponent<CheckCollision>(CHECKCOLLISION_H, static_cast<TopDownState*> (mngr_)->getplayer(), "portal");
		portalImage->setAnim("portalAnimated", 30, 10, 3, true);
		setCheckCollision = true;
	}
}

void PortalComponent::Teleport(Vector2D newPlayerPos) {
	trPlayer_->setPos(newPlayerPos);
}