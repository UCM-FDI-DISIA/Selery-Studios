#pragma once
#include "CheckCollision.h"
#include "utils/Entity.h"
using namespace std;
cmpId_type p = int(TRANSFORM_H);

CheckCollision::CheckCollision(PlayerTD* player,GameManager* gm_) :Component()
{
	player_ = player;
	gm = gm_;
}
void CheckCollision::initComponent() {
	tr1 = ent_->getComponent<Transform>(p);
	width1 = tr1->getW();
	height1 = tr1->getH();
	tr2 = player_->getComponent<Transform>(p);
	width2 = tr2->getW();
	height2 = tr2->getH();

	//rect1 = getRect1();
	//rect2 = getRect2();

}
void CheckCollision::update() 
{
	//drawCollider();
	/*rect1 = getRect1();
	rect2 = getRect2()*/;
	if (ent_->getComponent<Transform>(p))
	{
		//cout << "FIGHT!";
		if (Collision::collides(tr1->getPos(), width1 / 3, height1 / 3, tr2->getPos(), width2 / 3, height2 / 3))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			cout << "FIGHT!";
		}
		else if (Collision::collides(tr1->getPos(), width1, height1, tr2->getPos(), width2 / 7, height2))
		{
			cout << "as";//SDLUtils::instance()->soundEffects().at("prueba").play();
		}
	}
	else
	{
		cout << "LO QUE HACE EL NPC";
		
	}

	
}


void CheckCollision::drawCollider()
{ 
	
	SDL_SetRenderDrawColor(gm->getRenderer(), 255, 0, 255, 0);
	SDL_RenderDrawRect(gm->getRenderer(), &rect1);


	SDL_SetRenderDrawColor(gm->getRenderer(), 0, 0, 255, 0);
	SDL_RenderDrawRect(gm->getRenderer(), &rect2);

	SDL_RenderPresent(gm->getRenderer());

	SDL_SetRenderDrawColor(gm->getRenderer(), 0, 255, 255, 255);
}