#pragma once
#include "../Entities/LifeBar.h"
#include "../components/AnimationEnemyBEUComponent.h"
#include "../components/EnemyBEUDirectionComponent.h"
#include "../components/InputComponentBEU.h"
#include "../components/Image.h"

class LifeComponent : public Component
{
private:
#pragma region references
	LifeBar* lifeBar_ = nullptr;
	AnimationEnemyBEUComponent* anim_ = nullptr;
	EnemyBEUDirectionComponent* eMov_ = nullptr;
	InputComponentBEU* inp_ = nullptr;
	Image* im_ = nullptr;
#pragma endregion

#pragma region parameters
	float life_, maxLife_;
	float speed_ = 1.0f;
	bool die_ = false;
	bool hit = false;
	bool collision = false;
	bool enemy_ = false;
#pragma endregion
public:

	LifeComponent(float maxLife, LifeBar* lifeBar, bool enemy);
	void initComponent();

	void render();
	void update();
	void subLife(float damage);
	void subLifeDie(float damage);

	void Hit(float damage);
	void Death();

	
	void resetLife() { life_ = maxLife_; }
	float getLife() { return life_; }
	void setLifeBar(LifeBar* l) { lifeBar_ = l; }
	void setCollision(bool col) { collision = col; }
};

