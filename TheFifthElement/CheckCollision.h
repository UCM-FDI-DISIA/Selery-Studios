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
public:

	//Constructora de CheckCollision, esta recibe tanto el player como el manager, para tomar referencias
	//Y como valores el looking range, que es lo ancho que van a ser los rectangulos (el espacio que abarcan), el alto y la dirección, side
	//Este último valor toma dos únicos valores, 1 si mira a la derecha y -1 si mira a la izquierda
	CheckCollision(PlayerTD* player,GameManager* gm_,float lookingRange,float lookingWidth,float side);

	//Método en el que iniciamos y seteamos los valores necesarios desde un principio
	void initComponent();

	void update();
	void updateRects();

	//Método para crear y actualizar el rectángulo interior del enemigo el cual, si colisiona el personaje con él, será llevado al modo Beat Em Up
	inline SDL_Rect getRectFight() { return  build_sdlrect(tr1->getPos().getX()+ offset * - side_, tr1->getPos().getY() - (lookingHeight_ / 2)/2, lookingRange_+ 50 * side_, tr1->getH() + lookingHeight_/2); }
	
	//Método para crear y actualizar el rectángulo exterior del enemigo el cual, si colisiona el personaje con él, lo avisa con un sonido y con una imagen
	inline SDL_Rect getRectDetection() { return  build_sdlrect(tr1->getPos().getX() + offset*-side_, tr1->getPos().getY() - lookingHeight_/2, lookingRange_+ 200* side_, tr1->getH()+lookingHeight_); }							//lo que sume a getH()------> lo tengo que restar a la Y partido de 2------> si sumo 4, resto 2
	
	//Método para crear el rectángulo, en caso de ser un NPC
	inline SDL_Rect getNPCRect() { return build_sdlrect(tr1->getPos(), tr1->getW() / 7, tr1->getW()); }
	
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
