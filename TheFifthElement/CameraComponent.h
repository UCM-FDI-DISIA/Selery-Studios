#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H_
#include "Transform.h"
#include "Camera.h"

class CameraComponent : public Component
{
public:
	CameraComponent(GameManager* gm_, PlayerTD* player);
	void initComponent();
	void update();
	//void drawCollider();
	

private:
	Vector2D pos_;
	GameManager* gm_;
	Transform* camTr_;
	//Camera* cam_;
	Transform* playerTr_;
	PlayerTD* player_;
	SDL_Rect camRect_;
	
};
#endif