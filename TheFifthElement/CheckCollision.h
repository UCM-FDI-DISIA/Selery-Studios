#pragma once
#ifndef CHECKCOLLISION_H_
#define CHECKCOLLISION_H_
#include "Transform.h"
#include "utils/Vector2D.h"
#include "PlayerTD.h"
#include "Collision.h"
#include "sdlutils/SDLUtils.h"
#include "GameManager.h"
class CheckCollision : public Component
{
private:
	PlayerTD* player_;
	Transform* tr1;
	Transform* tr2;
	SDL_Rect rectFight, rectDetection, rectPlayer;
	GameManager* gm;
	float lookingRange_;
	float lookingHeight_;
	float offset;
	int side_;
public:
	CheckCollision(PlayerTD* player, GameManager* gm_);

	//Constructora de CheckCollision, esta recibe tanto el player como el manager, para tomar referencias
	//Y como valores el looking range, que es lo ancho que van a ser los rectangulos (el espacio que abarcan), el alto y la direcci?, side
	//Este ?ltimo valor toma dos ?nicos valores, 1 si mira a la derecha y -1 si mira a la izquierda
	CheckCollision(PlayerTD* player,GameManager* gm_,float lookingRange,float lookingWidth,float side);

	//M?odo en el que iniciamos y seteamos los valores necesarios desde un principio
	void initComponent();

	void update();
	void updateRects();

	//M?odo para crear y actualizar el rect?gulo interior del enemigo el cual, si colisiona el personaje con ?, ser?llevado al modo Beat Em Up
	inline SDL_Rect getRectFight() { return  build_sdlrect(tr1->getPos().getX()+ offset * - side_, tr1->getPos().getY() - (lookingHeight_ / 2)/2, lookingRange_+ 50 * side_, tr1->getH() + lookingHeight_/2); }
	
	//M?odo para crear y actualizar el rect?gulo exterior del enemigo el cual, si colisiona el personaje con ?, lo avisa con un sonido y con una imagen
	inline SDL_Rect getRectDetection() { return  build_sdlrect(tr1->getPos().getX() + offset*-side_, tr1->getPos().getY() - lookingHeight_/2, lookingRange_+ 200* side_, tr1->getH()+lookingHeight_); }							//lo que sume a getH()------> lo tengo que restar a la Y partido de 2------> si sumo 4, resto 2

	//M?odo para crear el rect?gulo, en caso de ser un NPC
	inline SDL_Rect getRectNPC() { return build_sdlrect(tr1->getPos(), tr1->getW() / 7, tr1->getH()); }
	
	//Equivalente para el personaje
	inline SDL_Rect getPlayerRect() { return build_sdlrect(tr2->getPos(), tr2->getW() / 7, tr2->getH()); }
	void render();
private:
	PlayerTD* player_;
	Transform* tr1;
	Transform* tr2;
	SDL_Rect rectFight,rectDetection,rectPlayer,rectNPC;
	GameManager* gm;
	float lookingRange_;
	float lookingHeight_;
	float offset;
	int side_;
	
};
#endif
