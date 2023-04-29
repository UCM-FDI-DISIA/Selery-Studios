#include "Trigger.h"
Trigger::Trigger() :Component() {
	this->colisions = colisions;
}
Trigger::~Trigger()
{
}
void Trigger::initComponent() {
}
void Trigger::update() {

	player->x = trans_player->getPos().getX();
	player->y = trans_player->getPos().getY();
	player->h = trans_player->getH();
	player->w = trans_player->getW();

	/*	trans_col = c->getComponent<Transform>(TRANSFORM_H);
		colision->h = trans_col->getH();
		colision->w = trans_col->getW();
		colision->x = trans_col->getPos().getX();
		colision->y = trans_col->getPos().getY();
		if (SDL_HasIntersection(player, colision)) {
			

		}*/
	

}



