#pragma once
#ifndef ANIMATIONLIGHTBOSSCOMPONENT_H_
#define ANIMATIONLIGHTBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "FramedImage.h"

class AnimationLightBossComponent: public Component
{
private:
	FramedImage* imBoss_;
	bool dead = false;
public:
	enum Animations {
		Idle, Attack, Hit, Die, Attack2
	};
	Animations currentAnim;
	AnimationLightBossComponent() {}
	virtual ~AnimationLightBossComponent() {}
	void update();
	void initComponent();
	void newAnim(Animations anim);
	void setDeath() { dead = true; }
};

#endif