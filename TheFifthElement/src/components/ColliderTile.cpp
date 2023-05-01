#include "ColliderTile.h"
#include "InputComponent.h"

ColliderTile::ColliderTile(vector<Entity*> colisions) :Component() {
	this->colisions = colisions;
}

ColliderTile::~ColliderTile() {
	delete colision;
	delete player;
	delete area;
}

void ColliderTile::initComponent() {
	trans_player = ent_->getComponent<Transform>(TRANSFORM_H);
	input = ent_->getComponent<InputComponent>(INPUTCOMPONENT_H);
	colision = new SDL_Rect();
	player = new SDL_Rect();
	area = new SDL_Rect();
}

void ColliderTile::update() {

	player->x = trans_player->getPos().getX();
	player->y = trans_player->getPos().getY() + 40 * WIN_HEIGHT / 600;
	player->h = trans_player->getH() - 50 * WIN_HEIGHT / 600;
	player->w = trans_player->getW();
	d = -1;
	for (auto c : colisions) {
			trans_col = c->getComponent<Transform>(TRANSFORM_H);
			colision->h = trans_col->getH();
			colision->w = trans_col->getW();
			colision->x = trans_col->getPos().getX();
			colision->y = trans_col->getPos().getY();

			if (SDL_IntersectRect(player, colision, area)) {
				//NONE = -1,
				//	UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, 
				//UPLEFT = 4, UPRIGHT = 5, DOWNLEFT = 6, DOWNRIGHT = 7
				
				if (area->y <  (colision->y+(colision->h/2))) { //por arriba
						//colisiona por la izquierda
						if (area->x <= (colision->x+(colision->w/2))) {
							if (area->w > area->h) {
								if (d == -1)  d = 1;
								else { //si ya estaba colisionando con algo
									if (d == 2)  d = 6;
									else if (d == 3) d = 7;
								}
							}
							else { 

								if (d == -1) d = 3;
								else {
									if (d == 1)  d = 7;
									else if (d == 0) d = 5;
								}
							}

							
						}
						else {
							//colisiona por la derecha
							if (area->w > area->h) {
								if (d == -1) d = 1;
								else {
									if (d == 2)  d = 6;
									else if (d == 3) d = 7;
								}
							}
							else  {
								if (d == -1) d = 2;
								else {
									if (d == 0)  d = 4;
									else if (d == 1) d = 6;
								}
							}
						}
				}
				else { // colisiona por abajo
					//colisiona por la izquierda
					if (area->x <= (colision->x+(colision->w/2))) {
						if (area->w > area->h) {
							if (d == -1) d = 0;
							else {
								if (d == 2)  d = 4;
								else if (d == 3) d = 5;
							}
						}
						else {
							if (d == -1) d = 3;
							else {
								if (d == 0)  d = 5;
								else if (d == 1) d = 7;
							}
						}
					
					}
					else {
						//colisiona por la derecha
						if (area->w > area->h) {
							if (d == -1) d = 0;
							else {
								if (d == 2)  d = 4;
								else if (d == 3) d = 5;
							}
						}
						else {
							if (d == -1) d = 2;
							else {
								if (d == 0)  d = 4;
								else if (d == 1) d = 6;
							}
						}
					}
				}
				
			}
	}
	input->setDirection(d);

}

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


