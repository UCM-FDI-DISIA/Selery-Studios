#include "LimitBEU.h"

LimitBEU::LimitBEU(bool staticCamera) {
	stCam_ = staticCamera;
}

void LimitBEU::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	jmp_ = ent_->getComponent<JumpComponent>(JUMP_H);
	downLimit = /*sdlutils().height()*/WIN_HEIGHT - (tr_->getH());
	topLimit = /*sdlutils().height()*/ WIN_HEIGHT * 0.3;
}

void LimitBEU::update() {
	
	//// l�mites verticales 
	if (tr_->getPos().getY() < topLimit && jmp_->isJumpEnabled()) { tr_->setPos(Vector2D(tr_->getPos().getX(), topLimit)); }
	else if (tr_->getPos().getY() > downLimit) { tr_->setPos(Vector2D(tr_->getPos().getX(), downLimit)); }
	
	// l�mites horizontales
	if (tr_->getPos().getX() < ( - 150  * tr_->getScaleW())) { tr_->setPos(Vector2D(-150 * tr_->getScaleW(), tr_->getPos().getY())); }
	else{

		if (stCam_ && tr_->getPos().getX() > WIN_WIDTH- (150 *tr_->getScaleW()+(tr_->getW()) / 2))
			tr_->setPos(Vector2D(WIN_WIDTH - (150 * tr_->getScaleW() + (tr_->getW() / 2)), tr_->getPos().getY()));

		else if	(tr_->getPos().getX() > BACKGROUNDBEU_WIDTH - (tr_->getW()) * 1.25)
			tr_->setPos(Vector2D(BACKGROUNDBEU_WIDTH - (tr_->getW()) * 1.25, tr_->getPos().getY()));
	}
}