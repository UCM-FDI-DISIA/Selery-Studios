#include "MovementEarthBossComponent.h"
MovementEarthBossComponent::MovementEarthBossComponent(Transform* tr) {
	playerTransform = tr;
}

void MovementEarthBossComponent::initComponent() {
	bossTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	bossTransform->setVel(1);
}

void MovementEarthBossComponent::update() {
	bossTransform->setDir(playerTransform->getPos() - bossTransform->getPos());
	bossTransform->setPos(bossTransform->getPos() + (bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2))) * bossTransform->getVel());
	cout << bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2)) << endl;
}