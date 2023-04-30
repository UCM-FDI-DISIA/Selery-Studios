#include "Trigger.h"
Trigger::Trigger(string name, Transform* trans_player_, Transform* trans_col):  Component() {
	

	colision->h = trans_col->getH();
	colision->w = trans_col->getW();
	colision->x = trans_col->getPos().getX();
	colision->y = trans_col->getPos().getY();
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
	

		//trans_col = c->getComponent<Transform>(TRANSFORM_H);
		
		if (SDL_HasIntersection(player, colision)) {
			

		}
	

}



