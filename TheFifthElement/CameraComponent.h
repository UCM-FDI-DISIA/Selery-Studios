#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H_
#include "Transform.h"
#include "GameManager.h"
#include "PlayerTD.h"

class CameraComponent : public Component
{
public:
	CameraComponent(GameManager* gm_, PlayerTD* player);
	void initComponent();
	void update();
	inline SDL_Rect getRect() { return build_sdlrect(camTr_->getPos(), camTr_->getW(), camTr_->getH()); }
	void render();
	

private:
	Vector2D pos_{ 0,0 };
	GameManager* gm_;
	Transform* camTr_;
	Transform* playerTr_;
	PlayerTD* player_;
	SDL_Rect camRect_;	
};
#endif