#pragma once
#include "../utils/Component.h"
#include <cstdlib>
#include "../utils/Constants.h"
#include "FramedImage.h"
#include "Transform.h"
#include "../states/BeatEmUpState.h"
#include "DisableOnExit.h"
#include "WaterBossLife.h"
#include "IceShadowComponent.h"
#include "IceIAComponent.h"

class WaterBossIA : public Component
{
private:
	float attackWavesPos_, attackIcePos_;
	enum State {
		NONE, WAVES, ICE,
	};
	State currentState_;
	FramedImage* im_;
	Transform* tr_;
	Transform* lastWave_;
	WaterBossLife* wLife_;

	Vector2D dir_;
	float wavePos_;
	float downLimit, topLimit;
	float offset, chrono;
	int cont;

	Entity* player_;
	//Entity* lastWave_ = nullptr;

	int iceCont_;
	int fila_;
	bool set_ = false;
public:
	WaterBossIA(Entity* player);
	void initComponent();
	void update();
	void newAttack();
	void attackWaves();
	void attackIce();
	void setIdle();
	void setWalk(Vector2D dir);
	void summonWave();
	Entity* createWave(float y);
	void addIce(int n);
	// metodo cambiar invulnerabilidad
};

