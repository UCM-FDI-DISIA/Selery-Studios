#pragma once
#ifndef ANIMATIONEARTHBOSSCOMPONENT_H_
#define ANIMATIONBOSSCOMPONENT_H_
#include "src/utils/Vector2D.h"
#include "src/utils/Component.h"
#include "src/utils/Entity.h"
#include "src/components/Image.h"

class AnimationEarthBossComponent : public Component
{
private:
	Image* imBoss;
public:
	enum Animations {
		Idle, Moving, Attack, Hit, Death, IdleProtection, Protection
	};
	Animations currentAnimation;

	AnimationEarthBossComponent() {};
	virtual ~AnimationEarthBossComponent() {}
	void initComponent();
	void newAnimation(Animations newAnim);
	void update();
};
#endif


