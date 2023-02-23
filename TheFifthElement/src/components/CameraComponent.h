#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H_
#include "Transform.h"
#include "../GameManager.h"
#include "../Entities/PlayerTD.h"

class CameraComponent : public Component
{
private:
	GameManager* gm_;
	Transform* playerTr_;
	PlayerTD* player_;
	SDL_Rect camRect_;
	Transform* camTr_;
public:
	CameraComponent(GameManager* gm, PlayerTD* player);
	void initComponent();
	void update();
	void render();
};
#endif
