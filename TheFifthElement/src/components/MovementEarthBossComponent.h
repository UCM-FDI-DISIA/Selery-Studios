#pragma once
#ifndef MOVEMENTEARTHBOSSCOMPONENT_H_
#define MOVEMENTEARTHBOSSCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "Transform.h"
#include "PointOfFightComponent.h"
#include "AnimationEarthBossComponent.h"

class MovementEarthBossComponent : public Component
{
private:
	Image* im_;
	AnimationEarthBossComponent* animator;
	Transform* playerTransform;
	Transform* bossTransform;
	PointOfFightComponent* fightPlayerComp;
	PointOfFightComponent* fightBossComp;
	Entity* player_;
	float marginToMove = 20; // Variable que controla lo suficientemente lejos que esta verticalmente el player
	float marginToAttack = 10; // Variable que controla lo suficientemente cerca que esta el player para poder atacar
	bool attack = false;
public:
	MovementEarthBossComponent(Entity* player);
	virtual ~MovementEarthBossComponent() {}
	void initComponent();
	void update();
	inline bool getAttack() { return attack; }
	inline void setAttack(bool newValue) { attack = newValue; }
};
#endif

