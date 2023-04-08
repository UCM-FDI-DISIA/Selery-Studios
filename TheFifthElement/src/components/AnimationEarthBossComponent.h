#pragma once
#ifndef ANIMATIONEARTHBOSSCOMPONENT_H_
#define ANIMATIONEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "FramedImage.h"

class AnimationEarthBossComponent : public Component
{
private:
	FramedImage* imBoss;
public:
	enum Animations {
		Idle, Moving, Attack, Hit, Death, IdleProtection, Protection, Null
	};
	Animations currentAnimation;
	Animations nextAnimation;

	AnimationEarthBossComponent() {};
	virtual ~AnimationEarthBossComponent() {}
	void initComponent();
	void newAnimation(Animations newAnim);
	void update();
};
#endif


