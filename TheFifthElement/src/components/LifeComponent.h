#pragma once
#include "../Entities/LifeBar.h"
#include "AnimationEnemyBEUComponent.h"

class LifeComponent : public Component {
private:
	AnimationEnemyBEUComponent* enemyIm = nullptr;
	LifeBar* lifeBar_;
	float life_, maxLife_;

public:
	LifeComponent(float maxLife, LifeBar* lifeBar);
	void initComponent();

	void update();
	void subLife(float damage);
	void subLifeDie(float damage);
	void resetLife() { life_ = maxLife_; }
	float getLife() { return life_; }
	void render();
	void setLifeBar(LifeBar* l) { lifeBar_ = l; }

	void playDamageSound();
	void playDieSound();
};

