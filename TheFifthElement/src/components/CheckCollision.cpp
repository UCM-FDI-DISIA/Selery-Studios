#pragma once
#include "CheckCollision.h"
#include "../utils/Entity.h"
#include "../Entities/Element.h"
using namespace std;
cmpId_type p = int(TRANSFORM_H);

CheckCollision::CheckCollision(Entity* player, string id) : Component() {
	player_ = player;
	id_ = id;
}

CheckCollision::CheckCollision(Entity* player, float lookingRange, float lookingWidth, float side) :Component() {
	player_ = player;
	side_ = side;								//side==-1 ------>mira a la derecha					//			side==1-------->mira a la izquierda
	lookingRange_ = lookingRange;
	lookingHeight_ = lookingWidth;

}
CheckCollision::CheckCollision(Entity* player, int npc) :Component() {
	player_ = player;
	npc_ = npc;

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
	if (ent_->hasComponent(ENEMY_MOVEMENT_TD_H))
	{
		rectFight = getRectFight();
		rectDetection = getRectDetection();
	}
	else {
		rectNPC = getRectNPC();
	}
	rectPlayer = getPlayerRect();

	enemies = ent_->hasComponent(ENEMY_MOVEMENT_TD_H);
	objects_ = ent_->hasComponent(OBJECTSCOMPONENT_H);
	
}
void CheckCollision::update() 
{
	if (enemies)
	{
    	if (Collision::collides(Vector2D(rectPlayer.x,rectPlayer.y), rectPlayer.w,rectPlayer.h, Vector2D(rectFight.x,rectFight.y),rectFight.w,rectFight.h))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			GameManager::instance()->goBeatEmUp();
		}
		else if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectDetection.x, rectDetection.y), rectDetection.w, rectDetection.h))
		{
			//SDLUtils::instance()->soundEffects().at("prueba").play();
		}

	}
	else if (objects_ && id_ == "portal") {
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(tr1->getPos().getX(), tr1->getPos().getY()), tr1->getW(), tr1->getH()))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			static_cast<Portal*>(ent_)->Teleport(Vector2D(700, 400));
		}
	}
	else if (objects_ && id_ == "element") {
		if (!static_cast<Element*>(ent_)->GetPicked() && Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(tr1->getPos().getX(), tr1->getPos().getY()), tr1->getW(), tr1->getH()))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			static_cast<Element*>(ent_)->SetPicked(true);
		}
	}
	else {
		
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectNPC.x, rectNPC.y), rectNPC.w, rectNPC.h))
		{
			//si colisiona con el npc
			if (!player_->hascol()) {
				player_->setCol(npc_);
				player_->setCollision(true);
			}
			
		}
		else {
			if (!player_->hascol()) {
			player_->setCol(-1);
			}
		}
		
	}
	updateRects();
}


void CheckCollision::render()
{ 
//	if (id_ != "portal" && id_ != "element") {
//		rectPlayer.x -= ent_->mngr_->camRect_.x;
//		rectPlayer.y -= ent_->mngr_->camRect_.y;
//		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0); // Renderizamos el rectangulo del player						
//		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectPlayer);
//
//		rectDetection.x -= ent_->mngr_->camRect_.x;
//		rectDetection.y -= ent_->mngr_->camRect_.y;
//		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 120, 50, 255, 0); //	Renderizamos el rectangulo de deteccion del enemigo						
//		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectDetection);
//
//		rectFight.x -= ent_->mngr_->camRect_.x;
//		rectFight.y -= ent_->mngr_->camRect_.y;		
//		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 225, 100, 255, 0); // Renderizamos el rectangulo de combate del enemigo
//		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectFight);
//		
//		rectNPC.x -= ent_->mngr_->camRect_.x;
//		rectNPC.y -= ent_->mngr_->camRect_.y;
//		
//		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 225, 100, 255, 0);
//		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectNPC);
//
//		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255); // ponemos el fondo a negro						
	//}
}

void CheckCollision::updateRects()														
{
	//Modo para actualizar los rect?gulos
	rectPlayer = getPlayerRect();
	rectFight = getRectFight();
	rectDetection = getRectDetection();
	rectNPC = getRectNPC();
	/*if (ent_->hasComponent(LIFECOMPONENT_H))
	{		
		rectFight = getRectFight();		
		rectDetection = getRectDetection();	
	}	
	else {
		rectNPC = getRectNPC();
	}*/
	
}