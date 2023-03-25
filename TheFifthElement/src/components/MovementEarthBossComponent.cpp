#include "MovementEarthBossComponent.h"
MovementEarthBossComponent::MovementEarthBossComponent(Entity* player) {
	player_ = player;
}

void MovementEarthBossComponent::initComponent() {
	playerTransform = player_->getComponent<Transform>(TRANSFORM_H);
	fightPlayerComp = player_->getComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H);

	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	animator = ent_->getComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	fightBossComp = ent_->getComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H);
	bossTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	bossTransform->setVel(1);
}

void MovementEarthBossComponent::update() {
	bool atRight = (fightPlayerComp->getPointRightFight().getX() - fightBossComp->getPointLeftFight().getX()) < 0; // Boss a la derecha del player
	bool atLeft = (fightBossComp->getPointRightFight().getX() - fightPlayerComp->getPointLeftFight().getX()) < 0; // Boss a la izquierda del player
	float verticalDistance = fightPlayerComp->getPointRightFight().getY() - fightBossComp->getPointLeftFight().getY();

	if (verticalDistance < 0 && verticalDistance < -marginToMove) {
		bossTransform->setDir(Vector2D(0, -1));
		animator->newAnimation(AnimationEarthBossComponent::Moving);
		bossTransform->setVel(0.75);
	}
	else if (verticalDistance > 0 && verticalDistance > marginToMove) {
		bossTransform->setDir(Vector2D(0, 1));
		animator->newAnimation(AnimationEarthBossComponent::Moving);
		bossTransform->setVel(0.75);
	}
	else {
		if (atRight) {
			bossTransform->setDir(Vector2D(-1, 0));
			animator->newAnimation(AnimationEarthBossComponent::Moving);
			im_->setFlip(SDL_FLIP_HORIZONTAL);
			bossTransform->setVel(1);

		}
		else if (atLeft) {
			bossTransform->setDir(Vector2D(1, 0));
			animator->newAnimation(AnimationEarthBossComponent::Moving);
			im_->setFlip();
			bossTransform->setVel(1);
		}
	}
	if (!attack ){////&& !im_->isAnimPlaying()) {
		bossTransform->setPos(bossTransform->getPos() + bossTransform->getDir() * bossTransform->getVel());
	}

	if (atRight && abs(fightPlayerComp->getPointRightFight().getX() - fightBossComp->getPointLeftFight().getX()) < marginToAttack) {
		attack = true;
		im_->setFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (atLeft && abs(fightPlayerComp->getPointLeftFight().getX() - fightBossComp->getPointRightFight().getX()) < marginToAttack) {
		attack = true;
		im_->setFlip();
	}
	else if (!atRight && !atLeft && abs(verticalDistance) < marginToMove) {
		attack = true;
	}
	else {
		attack = false;
	}
	/*cout << atRight << endl;
	cout << atLeft << endl;
	cout << " "  << endl;*/
	//bossTransform->setDir(playerTransform->getPos() - bossTransform->getPos());
	//bossTransform->setPos(bossTransform->getPos() + (bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2))) * bossTransform->getVel());
	//cout << bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2)) << endl;
	//cout << bossTransform->getPos() << endl;
	//bossTransform->setDir(fightPlayerComp->getPointRightFight() - fightBossComp->getPointLeftFight());
	//bossTransform->setPos(bossTransform->getPos() + (bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2))) * bossTransform->getVel());
}