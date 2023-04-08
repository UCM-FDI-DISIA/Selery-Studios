#pragma once
#ifndef BOSSCOLLISION_H_
#define BOSSCOLLISION_H_
#include "Transform.h"
#include "../utils/Vector2D.h"
#include "../utils/Collision.h"
#include "../sdlutils/SDLUtils.h"
#include "../GameManager.h"
#include "../utils/Entity.h"
#include "../states/TopDownState.h"
#include "../utils/ecs.h"

class BossCollision : public Component
{
private:
	Entity* player_;
	Transform* tr1;
	Transform* tr2;
	SDL_Rect rectPlayer, rectBoss;
	string boss_;
public:

	virtual ~BossCollision() {};
	inline SDL_Rect getPlayerRect() { return build_sdlrect(tr2->getPos(), tr2->getW(), tr2->getH()); }
	inline SDL_Rect getRectBoss() { return build_sdlrect(tr1->getPos(), tr1->getW(), tr1->getH()); }

	BossCollision(Entity* player, string boss)
	{
		player_ = player;
		boss_ = boss;
	}
	void initComponent()
	{
		tr1 = ent_->getComponent<Transform>(TRANSFORM_H);
		tr2 = player_->getComponent<Transform>(TRANSFORM_H);
		rectBoss = getRectBoss();
		rectPlayer = getPlayerRect();
	}
	void update()
	{
		updateRects();
		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectBoss.x, rectBoss.y), rectBoss.w, rectBoss.h))
		{
			Saving::instance()->setPos(Vector2D(3686, 807));
			GameManager::instance()->goBeatEmUp(true, ent_, boss_);
		}
	}
	void updateRects()
	{
		//Modo para actualizar los rect?gulos
		rectPlayer = getPlayerRect();
		rectBoss = getRectBoss();
	}
};

#endif