#pragma once
#include "CheckCollision.h"
#include "utils/Entity.h"
using namespace std;
cmpId_type p = int(TRANSFORM_H);

CheckCollision::CheckCollision(PlayerTD* player,GameManager* gm_, float lookingRange, float lookingWidth, float side) :Component()
{
	player_ = player;
	gm = gm_;
	side_ = side;				//side==-1 ------>mira a la derecha					//			side==1-------->mira a la izquierda
	lookingRange_ = lookingRange;
	lookingHeight_ = lookingWidth;

}
void CheckCollision::initComponent() {
	tr1 = ent_->getComponent<Transform>(p);
	//width1 = tr1->getW();									NO USAMOS ESTOS DATOS YA QUE USAMOS VALORES PASADOS POR EL DISEÑADOR PARA PASARL CREAR LAS AREAS DE ACCION
	//height1 = tr1->getH();
	tr2 = player_->getComponent<Transform>(p);
	

	lookingRange_ *=side_;


	
	offset = tr1->getW() / 7;
	if (side_==1)
	{
		offset = (tr1->getW() / 7)-60;
	}
	
	//rect1 = getRect1();
	//rect2 = getRect2();

}
void CheckCollision::update() 
{
	
	rectDetection1 = getRectDetection1();
	rectDetection2 = getRectDetection2();

	rectFight1 = getRectFight1();
	rectFight2 = getRectFight2();
	
	if (ent_->getComponent<Transform>(p))
	{
		//cout << "FIGHT!";
		if (Collision::collides(tr1->getPos(), tr1->getW() / 3, tr1->getH() / 3, tr2->getPos(), tr2->getW() / 7, tr2->getH() ))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			cout << "FIGHT!";
		}
		else if (Collision::collides(tr1->getPos(), tr1->getW() / 3, tr1->getH() / 3, tr2->getPos(), tr2->getW() / 7, tr2->getH()))
		{
			cout << "as";//SDLUtils::instance()->soundEffects().at("prueba").play();
		}
	}
	else
	{
		cout << "LO QUE HACE EL NPC";
		
	}

	//Revisar
	
}


void CheckCollision::render()
{ 
	
	SDL_SetRenderDrawColor(gm->getRenderer(), 120, 50, 255, 0);
	SDL_RenderDrawRect(gm->getRenderer(), &rectDetection1);
	SDL_RenderDrawRect(gm->getRenderer(), &rectDetection2);

	SDL_SetRenderDrawColor(gm->getRenderer(), 225, 100, 255, 0);
	SDL_RenderDrawRect(gm->getRenderer(), &rectFight1);
	SDL_RenderDrawRect(gm->getRenderer(), &rectFight2);



	

	SDL_SetRenderDrawColor(gm->getRenderer(), 0, 255, 255, 255);
}