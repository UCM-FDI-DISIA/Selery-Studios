#include "ColliderTile.h"
ColliderTile::ColliderTile(vector<Entity*> colisions) :Component() {
	this->colisions = colisions;
	

}
void ColliderTile::initComponent() {
	trans_player = ent_->getComponent<Transform>(TRANSFORM_H);
	input = ent_->getComponent<InputComponent>(INPUTCOMPONENT_H);
	colision = new SDL_Rect();
	player = new SDL_Rect();
	
	
}
void ColliderTile::update() {


	for (auto c : colisions) {
		trans_col = c->getComponent<Transform>(TRANSFORM_H);
		colision->h = trans_col->getH();
		colision->w = trans_col->getW();
		colision->x = trans_col->getPos().getX();
		colision->y = trans_col->getPos().getY();
		player->x = trans_player->getPos().getX();
		player->y = trans_player->getPos().getY();
		player->h = trans_player->getH();
		player->w = trans_player->getW();

		/*topLeft_ = trans_col->getPos();
		topRight_ = { trans_col->getPos().getX() + trans_col->getW(), trans_col->getPos().getY() };
		bottomLeft_ = { trans_col->getPos().getX(), trans_col->getPos().getY() + trans_col->getH() };
		bottomRight_ = { trans_col->getPos().getX() + trans_col->getW(), trans_col->getPos().getY() + trans_col->getH() };*/
		if (SDL_IntersectRect(player, colision, area)) {
			/*pTopLeft = trans_player->getPos();
			pBottomLeft = { pTopLeft.getX(), pTopLeft.getY() + trans_player->getH() };
			pTopRight = { pTopLeft.getX() + trans_player->getW(), pTopLeft.getY() };
			pBottonRight = { pTopRight.getX(), pTopRight.getY() + trans_player->getH() };*/
			// colision arriba

			// UP=0, DOWN=1, LEFT=2, RIGHT=3
			if (area->y < colision->y + (colision->h / 2)) {
					//colisiona por la izquierda
					if (area->x <= (colision->x + (colision->w / 2))) {
						if (area->w > area->h) d = 0;
						else d=2;
					}
					else {
						//colisiona por la derecha
						if (area->w > area->h) d = 0;
						else d = 3;
					}
			}
			else { // colisiona por abajo
					//colisiona por la izquierda
					if (area->x <= (colision->x + (colision->w / 2))) {
						if (area->w > area->h) d = 1;
						else d = 2;
					}
					else {
						//colisiona por la derecha
						if (area->w > area->h) d = 1;
						else d=3;
					}
			}
			input->setDirection(d);
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

	if (pTopLeft.getY() == bottomLeft_.getY() && pBottomLeft.getY() > bottomLeft_.getY()) {
		return 0;
	}
	else  if (pBottomLeft.getY() == topLeft_.getY() && pTopLeft.getY() < topLeft_.getY()) {
		return 1;
	}
  if (pTopLeft.getX() == topRight_.getX() && pTopRight.getX() > topRight_.getX()) {
		return 2;
	}
	else if (pTopRight.getX() ==topLeft_.getX() && pTopLeft.getX() < topLeft_.getX()) {
		return 2;
	}
	 
}


