#include "LimitBEU.h"

LimitBEU::LimitBEU() {

}

void LimitBEU::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	downLimit = sdlutils().height() - 100 - tr_->getH();
	topLimit = sdlutils().height() / 4;
}

void LimitBEU::update() {
	if (tr_->getPos().getY() < topLimit) { tr_->setPos(Vector2D(tr_->getPos().getX(), topLimit)); }
	else if (tr_->getPos().getY() > downLimit) { tr_->setPos(Vector2D(tr_->getPos().getX(), downLimit)); }
}