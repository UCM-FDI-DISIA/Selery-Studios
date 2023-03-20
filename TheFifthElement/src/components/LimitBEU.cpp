#include "LimitBEU.h"

LimitBEU::LimitBEU() {

}

void LimitBEU::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	jmp_ = ent_->getComponent<JumpComponent>(JUMP_H);
	downLimit = sdlutils().height() - 100 - tr_->getH();
	topLimit = sdlutils().height() / 4;
}

void LimitBEU::update() {
	if (tr_->getPos().getY() < topLimit && jmp_->isJumpEnabled()) { tr_->setPos(Vector2D(tr_->getPos().getX(), topLimit)); }
	else if (tr_->getPos().getY() > downLimit) { tr_->setPos(Vector2D(tr_->getPos().getX(), downLimit)); }
	if (tr_->getPos().getX() < -75) { tr_->setPos(Vector2D(-75, tr_->getPos().getY())); }
}