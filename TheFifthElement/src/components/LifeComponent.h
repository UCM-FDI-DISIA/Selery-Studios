#pragma once
#include "../Entities/LifeBar.h"

class LifeComponent : public Component
{
private:
	LifeBar* lifeBar_;
	float life_, maxLife_;
public:

	LifeComponent(float maxLife, LifeBar* lifeBar);

	void update();
	void subLife(float damage);
	void subLifeDie(float damage);
	void resetLife() { life_ = maxLife_; }
	float getLife() { return life_; }
	void render();
	void setLifeBar(LifeBar* l) { lifeBar_ = l; }
};

