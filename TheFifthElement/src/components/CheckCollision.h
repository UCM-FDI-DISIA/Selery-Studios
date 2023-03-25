#pragma once
#ifndef CHECKCOLLISION_H_
#define CHECKCOLLISION_H_
#include "Transform.h"
#include "../utils/Vector2D.h"
#include "../utils/Collision.h"
#include "../sdlutils/SDLUtils.h"
#include "../GameManager.h"
#include "ObjectsComponent.h"
#include "PortalComponent.h"
#include "Enemy_movementTD_component.h"
class CheckCollision : public Component
{
private:
	Entity* player_;
	Transform* tr1;
	Transform* tr2;
	ObjectsComponent* obj;
	PortalComponent* portal;
	Enemy_movementTD_component* enM_;
	SDL_Rect rectFight, rectDetection, rectPlayer;
	float lookingRange_;
	float lookingHeight_;
	float offset;
	int side_;
	bool enemies, objects_, demo = true;
	string id_;
public:
	CheckCollision(Entity* player, string id);

	//Constructora de CheckCollision, esta recibe tanto el player como el manager, para tomar referencias
	//Y como valores el looking range, que es lo ancho que van a ser los rectangulos (el espacio que abarcan), el alto y la direcci?, side
	//Este ?ltimo valor toma dos ?nicos valores, 1 si mira a la derecha y -1 si mira a la izquierda
	CheckCollision(Entity* player, float lookingRange, float lookingWidth, float side);

	//M?odo en el que iniciamos y seteamos los valores necesarios desde un principio
	void initComponent();

	void update();
	void updateRects();

	//M?odo para crear y actualizar el rect?gulo interior del enemigo el cual, si colisiona el personaje con ?, ser?llevado al modo Beat Em Up
	inline SDL_Rect getRectFight() {
		if (enM_->getState() == "left") return  build_sdlrect(tr1->getPos().getX(), tr1->getPos().getY() - (lookingHeight_ / 2) / 2, lookingRange_ + 50 * side_, tr1->getH() + lookingHeight_ / 2);
		else return  build_sdlrect(tr1->getPos().getX() - offset * side_, tr1->getPos().getY() - (lookingHeight_ / 2) / 2, (lookingRange_ + 50 * side_) * -1, tr1->getH() + lookingHeight_ / 2);
	}

	//M?odo para crear y actualizar el rect?gulo exterior del enemigo el cual, si colisiona el personaje con ?, lo avisa con un sonido y con una imagen
	inline SDL_Rect getRectDetection() {
		if (enM_->getState() == "left") return  build_sdlrect(tr1->getPos().getX(), tr1->getPos().getY() - lookingHeight_ / 2, lookingRange_ + 200 * side_, tr1->getH() + lookingHeight_);
		else return  build_sdlrect(tr1->getPos().getX() - offset * side_, tr1->getPos().getY() - lookingHeight_ / 2, (lookingRange_ + 200 * side_) * -1, tr1->getH() + lookingHeight_);
	}							//lo que sume a getH()------> lo tengo que restar a la Y partido de 2------> si sumo 4, resto 2


	//Equivalente para el personaje
	inline SDL_Rect getPlayerRect() { return build_sdlrect(tr2->getPos(), tr2->getW(), tr2->getH()); }
	void render();
};
#endif
