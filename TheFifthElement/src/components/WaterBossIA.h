#pragma once
#include "../utils/Component.h"
#include <cstdlib>
#include "../utils/Constants.h"
#include "FramedImage.h"
#include "Transform.h"

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
	Vector2D dir_;
public:
	WaterBossIA();
	void initComponent();
	void update();
	void newAttack();
	void attackWaves();
	void attackIce();
	void setIdle();
	void setWalk(Vector2D dir);
	// metodo cambiar invulnerabilidad
};

