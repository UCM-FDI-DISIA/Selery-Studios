#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "../GameManager.h"
#include "../components/CheckCollision.h"
#include "PlayerTD.h"
#include "../components/LifeComponent.h"
#include "../components/Enemy_movementTD_component.h"
#include "../components/ColliderComponent.h"


class Enemy : public Entity
{
private:
	Vector2D EnemyPosition_{ 700,150 };
	float speed_ = 0.5f;
	float EnemyWidth_ = ENEMYTD_WIDTH, EnemyHeight_ = ENEMYTD_HEIGHT, EnemyRotation_ = 1;
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	PlayerTD* player_;
	CheckCollision* ch;
	int nframes = 7;
	int fila_;
	float life_, maxLife_;
	bool matrix_ = false;
public:
	Enemy(PlayerTD* player, float maxLife);
	~Enemy() {}
	void update() {}
};

