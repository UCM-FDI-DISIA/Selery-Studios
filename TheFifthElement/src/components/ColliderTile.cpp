#include "ColliderTile.h"
ColliderTile::ColliderTile(vector<Entity*> colisions) :Component() {
	this->colisions = colisions;
	string p;
}
void ColliderTile::initComponent() {
	trans_player = ent_->getComponent<Transform>(TRANSFORM_H);
	input = ent_->getComponent<InputComponent>(INPUTCOMPONENT_H);
	
}
void ColliderTile::update() {

	for (auto c : colisions) {
		trans_col = c->getComponent<Transform>(TRANSFORM_H);
		topLeft_ = trans_col->getPos();
		topRight_ = { trans_col->getPos().getX() + trans_col->getW(), trans_col->getPos().getY() };
		bottomLeft_ = { trans_col->getPos().getX(), trans_col->getPos().getY() + trans_col->getH() };
		bottomRight_ = { trans_col->getPos().getX() + trans_col->getW(), trans_col->getPos().getY() + trans_col->getH() };
		if (Collision::collides(trans_player->getPos(), trans_player->getW(),
			trans_player->getH(), trans_col->getPos(), trans_col->getW(), trans_col->getH())) {
			pTopLeft = trans_player->getPos();
			pBottomLeft = { pTopLeft.getX(), pTopLeft.getY() + trans_player->getH() };
			pTopRight = { pTopLeft.getX() + trans_player->getW(), pTopLeft.getY() };
			pBottonRight = { pTopRight.getX(), pTopRight.getY() + trans_player->getH() };
			input->setDirection(chooseDirection());
		}
		else{
			input->setDirection(-1);
		}
		
	}
	//if (isActive_) {
	//	SDL_Rect rect = build_sdlrect(tr->getPos(), tr->getW(), tr->getH());
	//	if (p->collide(rect)) {
	//		isColliding_ = true;
	//		onPlayerCollision();
	//	}
	//	else if (isColliding_) { // La colisión estaba activa pero ha parado

	//		isColliding_ = false;
	//		//onPlayerCollisionExit();
	//	}
	//}
}
//void ColliderTile:: onPlayerCollision() {
//	int dir = chooseDirection();
//
//}
//void ColliderTile:: onPlayerCollisionExit() {
//
//}

int ColliderTile::chooseDirection() {

	// UP=0, DOWN=1, LEFT=2, RIGHT=3


	if (pTopLeft.getY() <= bottomLeft_.getY() && pBottomLeft.getY() > bottomLeft_.getY()) {
		return 0;
	}
	else if (pBottomLeft.getY() > topLeft_.getY() && pTopLeft.getY() < topLeft_.getY()) {
		return 1;
	}
	else if (pTopLeft.getX() < topRight_.getX() && pTopRight.getX() > topRight_.getX()) {
		return 2;
	}
	else if (pTopRight.getX() > topLeft_.getX() && pTopLeft.getX() < topLeft_.getX()) {
		return 2;
	}
	/*if (pTopLeft.getY() <= bottomLeft_.getY()) {
		return 0;
	}
	else if (pBottomLeft.getY() >= topLeft_.getY() && pTopLeft.getY() >= bottomLeft_.getY()) {
		return 1;
	}*/


	//if (topLeft_.getY() <= pBottomLeft.getY()) {
	//	return 1;
	//}
	//else if (bottomLeft_.getY() >= pTopLeft.getY()) {
	//	return 0;
	//}
	//else if (topRight_.getX() >= pTopLeft.getX()) {
	//	return 2;
	//}
	//else if (topLeft_.getX() <= pTopRight.getX()) {
	//	return 3;
	//}

	/*if (bottomLeft_.getY() <= pTopLeft.getY() + margin_) {
		return 0;
	}
	else if (topLeft_.getY() <= pBottonRight.getY() - margin_) {

		return 1;
	}
	else if (topLeft_.getX() >= pTopRight.getX() - margin_) {

		return 3;
	}
	else  if (topRight_.getX() <= pTopLeft.getX() + margin_){

		return 2;
	}*/
	

}
