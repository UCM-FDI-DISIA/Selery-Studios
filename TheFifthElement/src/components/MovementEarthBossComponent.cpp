#include "MovementEarthBossComponent.h"
MovementEarthBossComponent::MovementEarthBossComponent(Transform* tr) {
	playerTransform = tr;
}

void MovementEarthBossComponent::initComponent() {
	bossTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	bossTransform->setVel(1);
}

void MovementEarthBossComponent::update() {
	pointLeftFight = playerTransform->getPos();
	bossTransform->setDir(playerTransform->getPos() - bossTransform->getPos());
	bossTransform->setPos(bossTransform->getPos() + (bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2))) * bossTransform->getVel());
	//cout << bossTransform->getDir() / sqrt(pow(bossTransform->getPos().getX(), 2) + pow(bossTransform->getPos().getY(), 2)) << endl;
}

void MovementEarthBossComponent::render() {
	SDL_Rect rect = build_sdlrect(pointLeftFight.getX(), pointLeftFight.getY(), 10, 10);
	rect.x -= mngr_->camRect_.x;
	rect.y -= mngr_->camRect_.y;
	SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 255, 255, 0);
	SDL_RenderDrawRect(sdlutils().renderer(), &rect);
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
}