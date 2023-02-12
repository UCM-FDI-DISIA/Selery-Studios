#pragma once
#ifndef CHECKCOLLISION_H_
#define CHECKCOLLISION_H_
#include "Transform.h"
#include "utils/Vector2D.h"
#include "PlayerTD.h"
#include "Collision.h"
#include "sdlutils/SDLUtils.h"
class CheckCollision : public Component
{
public:

	CheckCollision(PlayerTD* player);
	void initComponent();
	void update();
private:
	PlayerTD* player_;
	Transform* tr1;
	Transform* tr2;
	float width1, width2, height1, height2;
};

#endif