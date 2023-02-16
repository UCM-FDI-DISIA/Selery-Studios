#pragma once
#include "./utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "GameManager.h"
#include "CheckCollision.h"
#include "PlayerBEU.h"
#include "LifeComponent.h"
class EnemyBEU :
    public Entity
{
private:
	Vector2D EnemyPosition_{ 450,150 };
	//float speed_ = 0.0f;
	float EnemyWidth_ = 600, EnemyHeight_ = 150, EnemyRotation_ = 1;
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	GameManager* m;
	PlayerBEU* player_;
	CheckCollision* ch;
	int nframes = 3;
	int fila_;
	float life_, maxLife_;
	bool matrix_ = false;
public:



	~EnemyBEU()
	{

	}

	EnemyBEU(GameManager* gm_, PlayerBEU* player, float maxLife) : Entity()
	{
		maxLife_ = maxLife;
		life_ = maxLife;
		m = gm_;
		float a = 1.0f;
		float lookingRange = 150.0f;
		float lookingWidth = 100.0f;
		tr = addComponent<Transform>(int(TRANSFORM_H), EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_, nframes, matrix_);
		t = new Texture(gm_->getRenderer(), "./assets/Enemies/Pack de 4/Water/WaterMushroom.png");
		player_ = player;
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		//ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, gm_, lookingRange, lookingWidth, a);
		// hacer un template para coger a ambos jugadores o algo así
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);
		addComponent<LifeComponent>(int(LIFECOMPONENT_H), m, tr, maxLife_);
	}
};

