#pragma once
#include "CheckCollision.h"
#include "utils/Entity.h"
using namespace std;
cmpId_type p = int(TRANSFORM_H);

CheckCollision::CheckCollision(PlayerTD* player,GameManager* gm_, float lookingRange, float lookingWidth, float side) :Component()
{
	player_ = player;
	gm = gm_;
	side_ = side;								//side==-1 ------>mira a la derecha					//			side==1-------->mira a la izquierda
	lookingRange_ = lookingRange;
	lookingHeight_ = lookingWidth;

}
void CheckCollision::initComponent() {
	//Hacemos los getComponent de los Transform
	tr1 = ent_->getComponent<Transform>(p);
	tr2 = player_->getComponent<Transform>(p);

	//Si queremos que el personaje mire a la izquierda, la anchura ser? negativa y esta se calcular? de otra manera -------> ver el script Collision.cpp 
	lookingRange_ *=side_;

	//Offset el cual sumamos a la posici? en X del enemigo
	offset = tr1->getW() / 7;
	if (side_==1)
	{
		offset = (tr1->getW() / 7)-60;
	}
	if (ent_->hasComponent(LIFECOMPONENT_H))
	{
		rectFight = getRectFight();
		rectDetection = getRectDetection();
	}
	else {
		rectNPC = getRectNPC();
	}
	rectPlayer = getPlayerRect();
	
}
void CheckCollision::update() 
{
	
	if (ent_->hasComponent(LIFECOMPONENT_H))
	{
    	if (Collision::collides(Vector2D(rectPlayer.x,rectPlayer.y), rectPlayer.w,rectPlayer.h, Vector2D(rectFight.x,rectFight.y),rectFight.w,rectFight.h))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			gm->goBeatEmUp();
		}
		else if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectDetection.x, rectDetection.y), rectDetection.w, rectDetection.h))
		{

			//SDLUtils::instance()->soundEffects().at("prueba").play();
		}
	}
	else
	{

		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectNPC.x, rectNPC.y), rectNPC.w, rectNPC.h))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{

			//si colisiona con el npc
			player_->setCol(1);

		}
		
	}
	updateRects();
	

	
}


void CheckCollision::render()
{ 
	//Nota---->Checkear si hacer comprobaciones aqu?o no

	SDL_SetRenderDrawColor(gm->getRenderer(), 0, 255, 0, 0);							//	Renderizamos el rect?gulo del player
	SDL_RenderDrawRect(gm->getRenderer(), &rectPlayer);
	
	SDL_SetRenderDrawColor(gm->getRenderer(), 120, 50, 255, 0);							//	Renderizamos el rect?gulo de detecci? del enemigo
	SDL_RenderDrawRect(gm->getRenderer(), &rectDetection);


	SDL_SetRenderDrawColor(gm->getRenderer(), 225, 100, 255, 0);
	SDL_RenderDrawRect(gm->getRenderer(), &rectFight);									// Renderizamos el rect?gulo de combate del enemigo
	

	SDL_SetRenderDrawColor(gm->getRenderer(), 225, 100, 255, 0);
	SDL_RenderDrawRect(gm->getRenderer(), &rectNPC);

	SDL_SetRenderDrawColor(gm->getRenderer(), 0, 0, 0, 255);							//ponemos el fondo a negro
}

void CheckCollision::updateRects()														
{
	//M?odo para actualizar los rect?gulos
	rectPlayer = getPlayerRect();
	if (ent_->hasComponent(LIFECOMPONENT_H))
	{
		rectFight = getRectFight();
		rectDetection = getRectDetection();
	}	
	else {
		rectNPC = getRectNPC();
	}
	
}