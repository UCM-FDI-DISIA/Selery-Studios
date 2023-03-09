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
#include "../Entities/LifeBar.h"
#include "../components/AttackBoxComponent.h"

class EnemyBEU :
    public Entity
{
private:

/*#pragma region propierties
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
	LifeBar* lb_;
	LifeComponent* lifeC_;
#pragma endregion

#pragma region parameters
	float speed_ = 1.0f;
	bool die_ = false;
	bool hit = false;
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

#pragma endregion*/


public:
	/*~EnemyBEU();

	EnemyBEU(Vector2D pos,PlayerBEU* player, float maxLife, string enemy, string type);*/
};

