#include "MovementEarthBossComponent.h"
MovementEarthBossComponent::MovementEarthBossComponent(Entity* player) {
	player_ = player;
}

void MovementEarthBossComponent::initComponent() {
	playerTransform = player_->getComponent<Transform>(TRANSFORM_H);
	fightPlayerComp = player_->getComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H);
	bossTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	bossTransform->setVel(1);
}

void MovementEarthBossComponent::update() {
	//bossTransform->setDir(playerTransform->getPos() - bossTransform->getPos());
	//bossTransform->setPos(bossTransform->getPos() + (bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2))) * bossTransform->getVel());
	//cout << bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2)) << endl;
	bossTransform->setDir(fightPlayerComp->getPointRightFight() - bossTransform->getPos());
	bossTransform->setPos(bossTransform->getPos() + (bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2))) * bossTransform->getVel());
}