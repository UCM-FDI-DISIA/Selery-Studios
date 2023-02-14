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

	CheckCollision(PlayerTD* player,GameManager* gm_);
	void initComponent();
	void update();
	inline SDL_Rect getRect1() { return build_sdlrect(tr1->getPos().getX() + 10, tr1->getPos().getY(), tr1->getW()/7 , tr1->getH() ); }
	inline SDL_Rect getRect2() { return build_sdlrect(tr2->getPos().getX(), tr2->getPos().getY(), tr2->getW() / 7, tr2->getH()); }
	void drawCollider();
private:
	PlayerTD* player_;
	Transform* tr1;
	Transform* tr2;
	SDL_Rect rect1, rect2;
	GameManager* gm;
	float width1, width2, height1, height2;
};
#endif