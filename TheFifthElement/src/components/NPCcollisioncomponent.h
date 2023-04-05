#pragma once
#ifndef NPCCOLLISIONCOMPONENT_H_
#define NPCCOLLISIONCOMPONENT_H_
#include "Transform.h"
#include "../utils/Vector2D.h"
#include "../utils/Collision.h"
#include "../sdlutils/SDLUtils.h"
#include "../GameManager.h"
#include "../components/Playernpc.h"
#include "../utils/Entity.h"
class NPCcollisioncomponent : public Component
{
private:
	PlayerNPC* plynpc;
	Entity* player_;
	Transform* tr1;
	Transform* tr2;
	SDL_Rect rectPlayer, rectNPC;
	Texture* interact_;
	SDL_Rect dest;
	bool visibility=false;
	Vector2D pos_;

	int npc_ = -1;
public:
	//NPCcollisioncomponent(Entity* player, int npc);
	virtual ~NPCcollisioncomponent() {};
	/*void initComponent();
	void update();
	void updateRects();*/

	//M?odo para crear el rect?gulo, en caso de ser un NPC
	inline SDL_Rect getRectNPC() { return build_sdlrect(tr1->getPos(), tr1->getW(), tr1->getH()); }

	//Equivalente para el personaje
	inline SDL_Rect getPlayerRect() { return build_sdlrect(tr2->getPos(), tr2->getW(), tr2->getH()); }
	NPCcollisioncomponent(Entity* player, int npc) {
		player_ = player;
		npc_ = npc;
	}
	void initComponent() {
		//Hacemos los getComponent de los Transform
		tr1 = ent_->getComponent<Transform>(TRANSFORM_H);
		tr2 = player_->getComponent<Transform>(TRANSFORM_H);
		plynpc = player_->getComponent<PlayerNPC>(PLAYERNPC_H);
		rectNPC = getRectNPC();
		rectPlayer = getPlayerRect();
		
	}
	void update()
	{
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectNPC.x, rectNPC.y), rectNPC.w, rectNPC.h))
		{
			plynpc->setcolnpc(npc_);	
			visibility = true;

		}
		else { visibility = false; }
		updateRects();

	}
	void updateRects()
	{
		//Modo para actualizar los rect?gulos
		rectPlayer = getPlayerRect();
		rectNPC = getRectNPC();
	}

	void render()
	{
		if(visibility==true)
		{
			SDL_Rect dest = { 100 * WIN_WIDTH / 900,100 * WIN_HEIGHT / 600,32 * WIN_WIDTH / 900,32 * WIN_HEIGHT / 600 };
			SDLUtils::instance()->images().at("E").render(dest);
		}
	}
};
#endif
