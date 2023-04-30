#include "Trigger.h"
#include "../Puzzle1.h"
#include "../states/TopDownState.h"
Trigger::Trigger(string name_, Transform* trans_player_, Transform* trans_col, FramedImage* framed_):  Component() {
	name = name_;
	framed = framed_;
	trans_player = trans_player_;
	colision = new SDL_Rect();
	player = new SDL_Rect();
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
	
		
	if (SDL_HasIntersection(player, colision)) {
		if (!istrigger_) {
			framed->setAnim("Calicelleno", 8,false,0);
			Puzzle1::instance()->add(name[2]);
		}
		istrigger_ = true;

	}
	else {
		istrigger_ = false; 
	}
	

}
void Trigger::setTexture() {
	framed->setAnim("Calice", 8, false, 0);
}
void Trigger::desbloqueozona()
{
	static_cast<TopDownState*>(mngr_)->desbloqueoZona();
}

