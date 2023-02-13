#pragma once
#include "CheckCollision.h"
#include "utils/Entity.h"
using namespace std;
cmpId_type p = int(TRANSFORM_H);

CheckCollision::CheckCollision(PlayerTD* player) :Component()
{
	player_ = player;
}
void CheckCollision::initComponent() {
	tr1 = ent_->getComponent<Transform>(p);
	width1 = tr1->getW();
	height1 = tr1->getH();
	tr2 = player_->getComponent<Transform>(p);
	width2 = tr2->getW();
	height2 = tr2->getH();


}
void CheckCollision::update() {


	if (Collision::collides(tr1->getPos(), width1 / 3, height1 / 3, tr2->getPos(), width2 / 3, height2 / 3))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
	{
		cout << "FIGHT!";
	}
	else if (Collision::collides(tr1->getPos(), width1, height1, tr2->getPos(), width2, height2))
	{
		SDLUtils::instance()->soundEffects().at("prueba").play();
	}

}