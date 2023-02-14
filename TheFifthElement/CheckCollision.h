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

	CheckCollision(PlayerTD* player,GameManager* gm_,float lookingRange,float lookingWidth,float side);
	void initComponent();
	void update();
	inline SDL_Rect getRectFight1() { return  build_sdlrect(tr1->getPos().getX()+ offset * -side_, tr1->getPos().getY()- (lookingHeight_ / 2)/2, lookingRange_+50 * side_, tr1->getH() + lookingHeight_/2); }
	inline SDL_Rect getRectFight2() { return build_sdlrect(tr2->getPos(), tr2->getW() / 7, tr2->getH() ); }
	inline SDL_Rect getRectDetection1() { return  build_sdlrect(tr1->getPos().getX() + offset*-side_, tr1->getPos().getY()-lookingHeight_/2, lookingRange_+200*side_, tr1->getH()+lookingHeight_); }							//lo que sume a getH()------> lo tengo que restar a la Y partido de 2------> si sumo 4, resto 2
	inline SDL_Rect getRectDetection2() { return build_sdlrect(tr2->getPos(), tr2->getW() / 7, tr2->getH()); }


	inline SDL_Rect getNPC() { return build_sdlrect(tr1->getPos(), tr1->getW() / 7, tr1->getW()); }
	void render();
private:
	PlayerTD* player_;
	Transform* tr1;
	Transform* tr2;
	SDL_Rect rectFight1, rectFight2,rectDetection1,rectDetection2;
	GameManager* gm;
	float lookingRange_;
	float lookingHeight_;
	float offset;
	int side_;
	
};
#endif