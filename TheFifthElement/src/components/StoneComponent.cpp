#include "StoneComponent.h"
void StoneComponent::initComponent() {
	imStone = ent_->getComponent<Image>(IMAGE_H);
}

void StoneComponent::stonePicked() {
	stones--;
	if (stones <= 0) {
		ent_->setAlive(false);
	}
	else {
		imStone->setTexture("stone" + to_string(stones));
	}
}