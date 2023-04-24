#include "LimitBEU.h"

LimitBEU::LimitBEU(bool staticCamera) {
	stCam_ = staticCamera;
}

void LimitBEU::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	jmp_ = ent_->getComponent<JumpComponent>(JUMP_H);
	downLimit = sdlutils().height() - tr_->getH();
	topLimit = sdlutils().height() * 0.4;
}

void LimitBEU::update() {
	
	// límites verticales
	if (tr_->getPos().getY() < topLimit && jmp_->isJumpEnabled()) { tr_->setPos(Vector2D(tr_->getPos().getX(), topLimit)); }
	else if (tr_->getPos().getY() > downLimit) { tr_->setPos(Vector2D(tr_->getPos().getX(), downLimit)); }
	
	// límites horizontales
	if (tr_->getPos().getX() < -tr_->getW() * 0.75) { tr_->setPos(Vector2D(-tr_->getW() * 0.75, tr_->getPos().getY())); }
	else{

		if (stCam_ && tr_->getPos().getX() > WIN_WIDTH - (tr_->getW()*tr_->getS()))
			tr_->setPos(Vector2D(WIN_WIDTH - (tr_->getW() * tr_->getS()), tr_->getPos().getY()));

		else if	(tr_->getPos().getX() > BACKGROUNDBEU_WIDTH - (tr_->getW() * tr_->getS()) * 1.25)
			tr_->setPos(Vector2D(BACKGROUNDBEU_WIDTH - (tr_->getW() * tr_->getS()) * 1.25, tr_->getPos().getY()));
	}
}