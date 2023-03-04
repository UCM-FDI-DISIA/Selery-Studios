#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "../GameManager.h"
#include "PlayerBEU.h"
#include "../components/LifeComponent.h"
#include "../components/MovementComponent.h"
#include "../components/EnemyBEUDirectionComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/ColDetectorComponent.h"
#include "../components/AnimationEnemyBEUComponent.h"

class EnemyBEU :
    public Entity
{
private:

#pragma region propierties
	Vector2D EnemyPosition_{ 751,150 };
#pragma endregion

#pragma region references
	Texture* t_;
	Transform* tr_;
	Transform* trPlayer_;
	PlayerBEU* player_;
	MovementComponent* mov_;
	EnemyBEUDirectionComponent* eMov_;
	ColliderComponent* col_;
	Image* im_;
	AnimationEnemyBEUComponent* anim_;
#pragma endregion

#pragma region parameters
	float speed_ = 1.0f;
#pragma endregion

#pragma region sprites
	string enemy_, type_;
	float EnemyWidthQUESISIRVE_ = ENEMYBEU_WIDTH, EnemyHeightQUESISIRVE_ = ENEMYBEU_HEIGHT, EnemyWidth_, EnemyHeight_, EnemyRotation_ = 1;
	int nframes_;
	int fila_ = 0;
	float life_, maxLife_;
	bool matrix_ = false;

	Vector2D offset_;
	float ColWidth_, ColHeight_;

	bool set_ = false;
#pragma endregion


public:
	~EnemyBEU();

	EnemyBEU(Vector2D pos,PlayerBEU* player, float maxLife, string enemy, string type);

	void collision(bool col);

	PlayerBEU* returnPlayer();

	void setOffset(Vector2D offset);

	void setCollider(Vector2D offset, float h, float w);

	void setColAnim(float EnemyWidth, float EnemyHeight, int nframes, Vector2D offset,
		float ColWidth, float ColHeight, Texture* t, bool Anim);
};

