#pragma once
#include "./utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/SDLUtils.h"
#include "GameManager.h"
#include "CheckCollision.h"
#include "PlayerBEU.h"
#include "LifeComponent.h"
#include "MovementComponent.h"
#include "EnemyBEUDirectionComponent.h"
class EnemyBEU :
    public Entity
{
private:

#pragma region propierties
	Vector2D EnemyPosition_{ 350,150 };
#pragma endregion

#pragma region references
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	GameManager* m;
	PlayerBEU* player_;
	CheckCollision* ch;
	MovementComponent* mov_;
	EnemyBEUDirectionComponent* eMov_;
#pragma endregion

#pragma region parameters
	float speed_ = 3.0f;
#pragma endregion

#pragma region sprites
	float EnemyWidth_ = 600, EnemyHeight_ = 150, EnemyRotation_ = 1;
	int nframes = 4;
	int fila_ = 0;
	float life_, maxLife_;
	bool matrix_ = false;
#pragma endregion


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
		t = &SDLUtils::instance()->images().at("BEU_wind_Mushroom");
		player_ = player;
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		//ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, gm_, lookingRange, lookingWidth, a);
		// hacer un template para coger a ambos jugadores o algo así
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);
		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov_ = addComponent<MovementComponent>(s);
		cmpId_type e = int(ENEMYBEUDIRECTIONCOMPONENT_H);
		eMov_ = addComponent<EnemyBEUDirectionComponent>(e, player);
		//addComponent<LifeComponent>(int(LIFECOMPONENT_H), m, tr, maxLife_);



		addComponent<LifeComponent>(int(LIFECOMPONENT_H), gm_, tr, maxLife_);
	}

	PlayerBEU* returnPlayer() {
		return player_;
	}
};

