#pragma once
#ifndef LIFEEARTHBOSSCOMPONENT_H_
#define LIFEEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "AnimationEarthBossComponent.h"
#include "ObjectsComponent.h"
#include "Image.h"
#include "StoneComponent.h"
#include "InputComponentBEU.h"
#include "ProtectionEarthBossComponent.h"
#include "MovementEarthBossComponent.h"
#include "AttackEarthBossComponent.h"
class BeatEmUpState;
class LifeEarthBossComponent : public Component
{
private:
	AttackEarthBossComponent* bossAttackComp;
	ColliderComponent* bossCol;
	MovementEarthBossComponent* bossMovement;
	AnimationEarthBossComponent* animEarthBoss;
	FramedImage* bossImage;
	Transform* bossTransform;
	int life, maxLife, stage = 1;

	float scale;

	float barWidth_, barHeight_;
	Texture* barTexture_;

	float backWidth_, backHeight_;
	Texture* backTexture_;

	float borderWidth_, borderHeight_;
	Texture* borderTexture_;
public:
	LifeEarthBossComponent();
	virtual ~LifeEarthBossComponent() {}
	void receiveDamage(float damage, float mul);
	void initComponent();
	void stageTwo();
	void stageThree();
	void render();
};
#endif

