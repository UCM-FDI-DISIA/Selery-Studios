#pragma once
#include "CheckCollision.h"
#include "../utils/Entity.h"
using namespace std;

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
void CheckCollision::initComponent() {
	//Hacemos los getComponent de los Transform
	tr1 = ent_->getComponent<Transform>(TRANSFORM_H);
	tr2 = player_->getComponent<Transform>(TRANSFORM_H);
	enM_ = ent_->getComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H);

	//Si queremos que el personaje mire a la izquierda, la anchura ser? negativa y esta se calcular? de otra manera -------> ver el script Collision.cpp 
	lookingRange_ *= side_;

	//Offset el cual sumamos a la posici? en X del enemigo
	offset = tr1->getW();
	/*if (side_==1)
	{
		offset = (tr1->getW() / 7)-60;
	}*/
	if (ent_->hasComponent(ENEMY_MOVEMENT_TD_H))
	{
		rectFight = getRectFight();
		rectDetection = getRectDetection();
	}
	rectPlayer = getPlayerRect();

	enemies = ent_->hasComponent(ENEMY_MOVEMENT_TD_H);
	objects_ = ent_->hasComponent(OBJECTSCOMPONENT_H);
	obj = ent_->getComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
	portal = ent_->getComponent<PortalComponent>(PORTALCOMPONENT_H);

}
void CheckCollision::update()
{
	if (enemies)
	{
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectFight.x, rectFight.y), rectFight.w, rectFight.h))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			GameManager::instance()->goBeatEmUp(ent_);
		}
		else if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectDetection.x, rectDetection.y), rectDetection.w, rectDetection.h))
		{
			//SDLUtils::instance()->soundEffects().at("prueba").play();
		}

	}
	else if (objects_ && id_ == "portal") {
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(tr1->getPos().getX(), tr1->getPos().getY()), tr1->getW() * tr1->getS(), tr1->getH() * tr1->getS()))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			//static_cast<Portal*>(ent_)->Teleport(Vector2D(700, 400));
			portal->Teleport(Vector2D(700, 400));
		}
	}
	else if (objects_ && id_ == "element") {
		//if (!static_cast<Element*>(ent_)->GetPicked() && Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(tr1->getPos().getX(), tr1->getPos().getY()), tr1->getW(), tr1->getH()))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		//{
		//	static_cast<Element*>(ent_)->SetPicked(true);
		//}
		if (!obj->getPicked() && Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(tr1->getPos().getX(), tr1->getPos().getY()), tr1->getW() * tr1->getS(), tr1->getH() * tr1->getS()))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			obj->setPicked(true);
			portal->elementEarned();
		}
	}
	updateRects();
}


void CheckCollision::render()
{
	if (id_ != "portal" && id_ != "element") {
		rectPlayer.x -= mngr_->camRect_.x;
		rectPlayer.y -= mngr_->camRect_.y;
		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0); // Renderizamos el rectangulo del player						
		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectPlayer);

		rectDetection.x -= mngr_->camRect_.x;
		rectDetection.y -= mngr_->camRect_.y;
		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 120, 50, 255, 0); //	Renderizamos el rectangulo de deteccion del enemigo						
		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectDetection);

		rectFight.x -= mngr_->camRect_.x;
		rectFight.y -= mngr_->camRect_.y;
		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 225, 100, 255, 0); // Renderizamos el rectangulo de combate del enemigo
		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectFight);

		/*rectNPC.x -= mngr_->camRect_.x;
		rectNPC.y -= mngr_->camRect_.y;

		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 225, 100, 255, 0);
		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &rectNPC);*/

		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255); // ponemos el fondo a negro						
	}
}

void CheckCollision::updateRects()
{
	//Modo para actualizar los rect?gulos
	rectPlayer = getPlayerRect();
	rectFight = getRectFight();
	rectDetection = getRectDetection();
	/*if (ent_->hasComponent(LIFECOMPONENT_H))
	{
		rectFight = getRectFight();
		rectDetection = getRectDetection();
	}
	else {
		rectNPC = getRectNPC();
	}*/

}