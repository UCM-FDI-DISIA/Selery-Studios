#include "ColliderTile.h"
ColliderTile::ColliderTile(vector<Entity*> colisions) :Component() {
	this->colisions = colisions;
	string p;
}
void ColliderTile::initComponent() {
	trans_player = ent_->getComponent<Transform>(TRANSFORM_H);
	input = ent_->getComponent<InputComponent>(INPUTCOMPONENT_H);
	pTopLeft = trans_player->getPos();
	pBottomLeft = { pTopLeft.getX(), pTopLeft.getY() + trans_player->getH() };
	pTopRight = { pTopLeft.getX() + trans_player->getW(), pTopLeft.getY() };
	pBottonRight = { pTopRight.getX(), pTopRight.getY() + trans_player->getH() };
}
void ColliderTile::update() {

	for (auto c : colisions) {
		Transform* trans_col = c->getComponent<Transform>(TRANSFORM_H);
		topLeft_ = trans_col->getPos();
		topRight_ = { trans_col->getPos().getX() + trans_col->getW(), trans_col->getPos().getY() };
		bottomLeft_ = { trans_col->getPos().getX(), trans_col->getPos().getY() + trans_col->getH() };
		bottomRight_ = { trans_col->getPos().getX() + trans_col->getW(), trans_col->getPos().getY() + trans_col->getH() };
		if (Collision::collides(trans_player->getPos(), trans_player->getW(),
			trans_player->getH(), trans_col->getPos(), trans_col->getW(), trans_col->getH())) {
			input->setDirection(chooseDirection());
		}
		input->setDirection(-1);
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

	if (bottomLeft_.getY() <= pTopLeft.getY() + margin_) {
		return 0;
	}
	else if (topLeft_.getY() >= pBottonRight.getY() - margin_) {

		return 1;
	}
	else if (topLeft_.getX() >= pTopRight.getX() - margin_) {

		return 3;
	}
	else { // if (topRight_.getX() <= pTopLeft().getX() + margin_)

		return 2;
	}

}
