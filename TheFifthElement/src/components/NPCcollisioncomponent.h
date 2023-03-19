#pragma once
#ifndef NPCCOLLISIONCOMPONENT_H_
#define NPCCOLLISIONCOMPONENT_H_
#include "Transform.h"
#include "../utils/Vector2D.h"
#include "../utils/Collision.h"
#include "../sdlutils/SDLUtils.h"
#include "../GameManager.h"
#include "../components/Playernpc.h"
class NPCcollisioncomponent : public Component
{
private:
	PlayerNPC* plynpc;
	Entity* player_;
	Transform* tr1;
	Transform* tr2;
	SDL_Rect rectPlayer, rectNPC;
	int npc_ = -1;
public:
	NPCcollisioncomponent(Entity* player, int npc);

	//M?odo en el que iniciamos y seteamos los valores necesarios desde un principio
	void initComponent();

	void update();
	void updateRects();

	//M?odo para crear el rect?gulo, en caso de ser un NPC
	inline SDL_Rect getRectNPC() { return build_sdlrect(tr1->getPos(), tr1->getW(), tr1->getH()); }

	//Equivalente para el personaje
	inline SDL_Rect getPlayerRect() { return build_sdlrect(tr2->getPos(), tr2->getW(), tr2->getH()); }
};
#endif
