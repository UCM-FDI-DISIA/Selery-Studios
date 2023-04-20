#pragma once
#include "CheckCollision.h"
#include "../utils/Entity.h"
using namespace std;

CheckCollision::CheckCollision(Entity* player, string id) : Component() {
	player_ = player;
	id_ = id;
}

CheckCollision::CheckCollision(Entity* player, float lookingRange, float lookingWidth, float side, float offset, string boss) :Component() {
	player_ = player;
	side_ = side;								//side==-1 ------>mira a la derecha					//			side==1-------->mira a la izquierda
	lookingRange_ = lookingRange;
	lookingHeight_ = lookingWidth;
	boss_ = boss;
	ofs_ = offset;
}
void CheckCollision::initComponent() {
	//Hacemos los getComponent de los Transform
	tr1 = ent_->getComponent<Transform>(TRANSFORM_H);
	tr2 = player_->getComponent<Transform>(TRANSFORM_H);
	enM_ = ent_->getComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H);

	//Si queremos que el personaje mire a la izquierda, la anchura ser? negativa y esta se calcular? de otra manera -------> ver el script Collision.cpp 
	lookingRange_ *= side_;

	//Offset el cual sumamos a la posici? en X del enemigo
	if (ofs_ == 0) offset = tr1->getW();
	else offset = ofs_;
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
	portal = ent_->getComponent<PortalComponent>(PORTALCOMPONENT_H);

}
void CheckCollision::update()
{
	updateRects();
	if (enemies)
	{
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectFight.x, rectFight.y), rectFight.w, rectFight.h))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			Saving::instance()->setPos(Vector2D(3686, 807));
			if(boss_ == "")GameManager::instance()->goBeatEmUp(false, ent_, boss_);
			else GameManager::instance()->goBeatEmUp(true, ent_, boss_);
		}
		else if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectDetection.x, rectDetection.y), rectDetection.w, rectDetection.h))
		{
			//SDLUtils::instance()->soundEffects().at("prueba").play();
		}

	}
	else if (id_ == "portal") {
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(tr1->getPos().getX(), tr1->getPos().getY()), tr1->getW() * tr1->getS(), tr1->getH() * tr1->getS()))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			portal->Teleport(Vector2D(800, 800)); // Al mapa de luz
		}
	}
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
		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 100, 255, 0); // Renderizamos el rectangulo de combate del enemigo
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
	if (enemies) {
		rectFight = getRectFight();
		rectDetection = getRectDetection();
	}
	/*if (ent_->hasComponent(LIFECOMPONENT_H))
	{
		rectFight = getRectFight();
		rectDetection = getRectDetection();
	}
	else {
		rectNPC = getRectNPC();
	}*/

}