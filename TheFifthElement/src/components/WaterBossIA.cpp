#include "WaterBossIA.h"


WaterBossIA::WaterBossIA(){
	currentState_ = NONE;

	attackIcePos_ = WIN_WIDTH / 2;
	attackWavesPos_ = WIN_WIDTH * 9 / 11;
}

void WaterBossIA::initComponent() {
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

void WaterBossIA::update() {
	if (currentState_ == NONE) newAttack(); // no ataca
	else {
		// ataque olas
		if (currentState_ == WAVES) {
			if (!(abs(tr_->getPos().getX() - attackWavesPos_) >= 3)) {
				setIdle();
				tr_->setDir(Vector2D(0, 0));
			}
		}
		// ataque hielo
		else {
			if (!(abs(tr_->getPos().getX() - attackIcePos_) >= 3)) {
				setIdle();
				tr_->setDir(Vector2D(0, 0));
			}
		}
	}
}

void WaterBossIA::newAttack() {
	int rnd_ = rand() % 2;
	if (rnd_ == 0) attackWaves();
	else attackIce();
}

void WaterBossIA::attackWaves(){
	currentState_ = WAVES;
	dir_ = Vector2D(attackWavesPos_ - tr_->getPos().getX(), 0).normalize();
	tr_->setDir(dir_);
	setWalk(dir_);
}

void WaterBossIA::attackIce() {
	currentState_ = ICE;
	dir_ = Vector2D(attackIcePos_ - tr_->getPos().getX(), 0).normalize();
	tr_->setDir(dir_);
	setWalk(dir_);
}

void WaterBossIA::setIdle() {
	im_->setFlip(SDL_FLIP_NONE);
	im_->setAnim("waterBoss_idle", 6, false);
	////im_->setAnim(false, 0, 6, 0, 6);
}

void WaterBossIA::setWalk(Vector2D dir) {
	if (dir.getX() > 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else im_->setFlip(SDL_FLIP_NONE);
	im_->setAnim("waterBoss_walk", 10, false);
	////im_->setAnim(false, 1, 10, 0, 10);
}