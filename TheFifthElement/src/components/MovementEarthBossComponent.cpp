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
	if (!bossProtected) {
		bool atRight = (fightPlayerComp->getPointRightFight().getX() - fightBossComp->getPointLeftFight().getX()) < 0; // Boss a la derecha del player
		bool atLeft = (fightBossComp->getPointRightFight().getX() - fightPlayerComp->getPointLeftFight().getX()) < 0; // Boss a la izquierda del player
		float verticalDistance = fightPlayerComp->getPointRightFight().getY() - fightBossComp->getPointLeftFight().getY();

		if (verticalDistance < 0 && verticalDistance < -marginToMove) { // Si no esta en la misma vertical el golem se reposiciona verticalmente
			bossTransform->setDir(Vector2D(0, -1));
			animator->newAnimation(AnimationEarthBossComponent::Moving);
			bossTransform->setVel(0.75);
		}
		else if (verticalDistance > 0 && verticalDistance > marginToMove) {
			bossTransform->setDir(Vector2D(0, 1));
			animator->newAnimation(AnimationEarthBossComponent::Moving);
			bossTransform->setVel(0.75);
		}
		else { // Si esta en la misma vertical el golem se reposiciona horizontalmente
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
		if (!attack && !im_->getIsAnimUnstoppable()) { // Se mueve cuando no esta atacando
			bossTransform->setPos(bossTransform->getPos() + bossTransform->getDir() * bossTransform->getVel());
		}

		if (atRight && abs(fightPlayerComp->getPointRightFight().getX() - fightBossComp->getPointLeftFight().getX()) < marginToAttack) { // Ataque hacia la derecha
			attack = true;
			im_->setFlip(SDL_FLIP_HORIZONTAL);
		}
		else if (atLeft && abs(fightPlayerComp->getPointLeftFight().getX() - fightBossComp->getPointRightFight().getX()) < marginToAttack) { // Ataque hacia la izquierda
			attack = true;
			im_->setFlip();
		}
		else if (!atRight && !atLeft && abs(verticalDistance) < marginToMove) { // Ataque cuando el jugador se mete dentro del golem
			attack = true;
		}
		else {
			attack = false;
		}
	}
}