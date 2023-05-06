#include "LimitBEU.h"

LimitBEU::LimitBEU(string type) {
	type_ = type;
}

void LimitBEU::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	jmp_ = ent_->getComponent<JumpComponent>(JUMP_H);
	
	if (type_ == "water") {
		downLimit = WIN_HEIGHT - (tr_->getH());
		topLimit = WIN_HEIGHT * 0.18;
		rightLimit = WIN_WIDTH -  (50 * tr_->getScaleW() + (tr_->getW()) / 2);
	}
	else if (type_ == "fire") {
		downLimit = WIN_HEIGHT - (tr_->getH());
		topLimit = WIN_HEIGHT * 0.43;
		rightLimit = WIN_WIDTH - (50 * tr_->getScaleW() + (tr_->getW()) / 2);
	}
	else if (type_ == "light") {
		downLimit = WIN_HEIGHT - (tr_->getH()*1.25);
		topLimit = WIN_HEIGHT * 0.25;
		rightLimit = BACKGROUNDLIGHTBOSS_WIDTH- (250 * WIN_WIDTH / 900); // si es camara fija cambiar por WIN_WIDTH - (50 * tr_->getScaleW() + (tr_->getW()) / 2)
	}
	// fondo normal y jefe de tierra
	else {
		downLimit = WIN_HEIGHT * 0.44;
		topLimit = WIN_HEIGHT * 0.29;
		rightLimit = BACKGROUNDLIGHTBOSS_WIDTH -(290*WIN_WIDTH/900);
	}
}

void LimitBEU::update() {
	
	//// límites verticales 
	if (tr_->getPos().getY() < topLimit && jmp_->isJumpEnabled()) { tr_->setPos(Vector2D(tr_->getPos().getX(), topLimit)); }
	else if (tr_->getPos().getY() > downLimit) { tr_->setPos(Vector2D(tr_->getPos().getX(), downLimit)); }
	
	// límites horizontales
	if (tr_->getPos().getX() < ( - 180  * tr_->getScaleW())) { tr_->setPos(Vector2D(-180 * tr_->getScaleW(), tr_->getPos().getY())); }
	else if (tr_->getPos().getX() > rightLimit) { tr_->setPos(Vector2D(rightLimit, tr_->getPos().getY())); }
}