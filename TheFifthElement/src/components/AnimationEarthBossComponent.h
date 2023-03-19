#pragma once
#ifndef ANIMATIONEARTHBOSSCOMPONENT_H_
#define ANIMATIONEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "../components/Image.h"

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


