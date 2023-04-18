#include "StoneComponent.h"
StoneComponent::StoneComponent(int bossStage_) {
	bossStage = bossStage_;
}

void StoneComponent::initComponent() {
	imStone = ent_->getComponent<Image>(IMAGE_H);
}

void StoneComponent::stonePicked() {
	stones--;
	if (stones <= 0) {
		ent_->setAlive(false);
	}
	else {
		imStone->setTexture("v" + to_string(bossStage) + "stone" + to_string(stones));
	}
}