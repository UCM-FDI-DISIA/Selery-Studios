#pragma once
#include "../components/AnimationEnemyBEUComponent.h"
#include "../components/EnemyBEUDirectionComponent.h"
#include "../components/InputComponentBEU.h"
#include "../components/Image.h"

class LifeComponent : public Component {
private:
#pragma region references
	AnimationEnemyBEUComponent* anim_ = nullptr;
	EnemyBEUDirectionComponent* eMov_ = nullptr;
	InputComponentBEU* inp_ = nullptr;
	Image* im_ = nullptr;
	Transform* entTransform_ = nullptr;
#pragma endregion

#pragma region parameters
	float life_, maxLife_;
	float speed_ = 1.0f;
	bool die_ = false;
	bool hit_ = false;
	bool collision = false;
	bool enemy_ = false;
	string type_;
#pragma endregion

#pragma region propierties
	Vector2D pos_;
#pragma endregion

#pragma region LifeBar
	float barWidth_, barHeight_;
	Texture* barTexture_;
#pragma endregion

#pragma region LifeBarBack
	float backWidth_, backHeight_;
	Texture* backTexture_;
#pragma endregion

#pragma region LifeBarBorder
	float borderWidth_, borderHeight_;
	Texture* borderTexture_;
#pragma endregion

public:

	LifeComponent(float maxLife, bool enemy, string type, Entity* ent);
	void initComponent();

	void render();
	void update();
	void subLife(float damage);

	void Hit(float damage);
	void Death();


	void resetLife() { life_ = maxLife_; }
	float getLife() { return life_; }
	void setCollision(bool col) { collision = col; }

	void chooseTexture();
	
	void playDamageSound();
	void playDieSound();
};

