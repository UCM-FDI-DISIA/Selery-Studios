#pragma once
#ifndef ATTACKLIGHTBOSSCOMPONENT_H_
#define ATTACKLIGHTBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "Transform.h"
#include "FramedImage.h"
#include "MovementLightBossComponent.h"
#include "MovementComponent.h"
#include "DisableOnExit.h"
#include "LightBossElement.h"
#include "../GameManager.h"
#include "AnimationLightBossComponent.h"

class AttackLightBossComponent : public Component
{
private:
	int fightState;
	Entity* player_;
	MovementLightBossComponent* movBoss_;
	Transform* playerTrans;
	Transform* bossTrans;
	float distX, distY;
	float closeX = 200;
	float negCloseX = -200;
	Vector2D dirAtk;
	Vector2D dirMov;
	int timer;
	int timerRand;
	int opacity = 0;
	bool blacker = true;
	int contAtks;
	Transform* arrowTrans_;
	FramedImage* arrowIm_;
	Transform* rayTrans_;
	GameManager* Gm_;
	SDL_Rect BSrect = { 0,0,BACKGROUNDBEU_WIDTH,BACKGROUNDBEU_HEIGHT };
	SDL_Rect BSsrc = { 0,0,100,100 };
	Texture* blackScreenTex_;
	RandomNumberGenerator* random;
	FramedImage* imBoss_;
	bool attacking = false;
	bool atk1 = false;
	bool atk2 = false;
	Vector2D dirToPlayer;
	AnimationLightBossComponent* animBoss_;

public:
	AttackLightBossComponent(Entity* player);
	void initComponent();
	void setState(int state);
	void update();
	void attack1();
	void attack2();
	void render();
	void shootArrow(); //para solo disparar una flecha de luz
	void anim1(); //para hacer la animacion y al terminarla atacar
	bool isAtkn() { return attacking; }
};

#endif