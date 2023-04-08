#pragma once
#include "../utils/Component.h"
#include <cstdlib>
#include "../utils/Constants.h"
#include "Image.h"
#include "Transform.h"
#include "../states/BeatEmUpState.h"
#include "DisableOnExit.h"

class WaterBossIA : public Component
{
private:
	float attackWavesPos_, attackIcePos_;
	enum State {
		NONE, WAVES, ICE,
	};
	State currentState_;
	Image* im_;
	Transform* tr_;
	Transform* lastWave_;
	Vector2D dir_;
	float wavePos_;
	float downLimit, topLimit;
	float offset, chrono;
	int cont;
	Entity* player_;
	//Entity* lastWave_ = nullptr;
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
	// metodo cambiar invulnerabilidad
};

