#pragma once
#ifndef LIFELIGHTBOSSCOMPONENT_H_
#define LIFELIGHTBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "Transform.h"
#include "FramedImage.h"
#include "../states/BeatEmUpState.h"
#include "AttackLightBossComponent.h"

class LifeLightBossComponent: public Component
{
private:
	int maxLife=20000;
	int life;
	float scale;
	int fightState;
	AttackLightBossComponent* atk_;

	float barWidth_, barHeight_;
	Texture* barTexture_;

	float backWidth_, backHeight_;
	Texture* backTexture_;

	float borderWidth_, borderHeight_;
	Texture* borderTexture_;

	FramedImage* im_;
	Transform* tr_;

public:
	LifeLightBossComponent();
	void damage(float dam);
	void render();
	void initComponent();
	void checkState();
	virtual ~LifeLightBossComponent() {}
};

#endif