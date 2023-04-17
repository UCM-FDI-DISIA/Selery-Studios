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
	FramedImage* im_;
	AnimationEarthBossComponent* animator;
	Transform* playerTransform;
	Transform* bossTransform;
	PointOfFightComponent* fightPlayerComp;
	PointOfFightComponent* fightBossComp;
	Entity* player_;
	float marginToMove = 20; // Variable que controla lo suficientemente lejos que esta verticalmente el player
	float marginToAttack = 5; // Variable que controla lo suficientemente cerca que esta el player para poder atacar
	bool attack = false;
	bool bossProtected = false;
public:
	MovementEarthBossComponent(Entity* player);
	virtual ~MovementEarthBossComponent() {}
	void initComponent();
	void update();
	inline bool getAttack() { return attack; }
	inline void setAttack(bool newValue) { attack = newValue; }

	inline bool getBossProtected() { return bossProtected; }
	inline void setBossProtected(bool newValue) { bossProtected = newValue; }

	inline void setMarginToAttack(int newValue) { marginToAttack = newValue; }
};
#endif

