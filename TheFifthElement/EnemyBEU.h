#pragma once
#include "./utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "GameManager.h"
#include "CheckCollision.h"
#include "PlayerBEU.h"
<<<<<<< Updated upstream:TheFifthElement/EnemyBEU.h
#include "LifeComponent.h"
#include "MovementComponent.h"
#include "EnemyBEUDirectionComponent.h"
=======
#include "../components/LifeComponent.h"
#include "../components/MovementComponent.h"
#include "../components/EnemyBEUDirectionComponent.h"
#include "../../ColDetectorComponent.h"
>>>>>>> Stashed changes:TheFifthElement/src/Entities/EnemyBEU.h
class EnemyBEU :
    public Entity
{
private:

#pragma region propierties
	Vector2D EnemyPosition_{ 800,150 };
#pragma endregion

#pragma region references
	Texture* t;
	Transform* tr_;
	Transform* trPlayer_;
	GameManager* m;
	PlayerBEU* player_;
	CheckCollision* ch;
	MovementComponent* mov_;
	EnemyBEUDirectionComponent* eMov_;
#pragma endregion

#pragma region parameters
	float speed_ = 1.0f;
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
<<<<<<< Updated upstream:TheFifthElement/EnemyBEU.h
		tr = addComponent<Transform>(int(TRANSFORM_H), EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_, nframes, matrix_);
		t = new Texture(gm_->getRenderer(),"./assets/Enemies/Pack/Wind/WindSkeleton/idle.png");
=======
		tr_ = addComponent<Transform>(int(TRANSFORM_H), EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_,speed_, nframes, matrix_);
		t = &SDLUtils::instance()->images().at("BEU_wind_Mushroom");
>>>>>>> Stashed changes:TheFifthElement/src/Entities/EnemyBEU.h
		player_ = player;
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		//ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_, gm_, lookingRange, lookingWidth, a);
		// hacer un template para coger a ambos jugadores o algo as�
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);
		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov_ = addComponent<MovementComponent>(s);
		cmpId_type e = int(ENEMYBEUDIRECTIONCOMPONENT_H);
		eMov_ = addComponent<EnemyBEUDirectionComponent>(e, player);
<<<<<<< Updated upstream:TheFifthElement/EnemyBEU.h
		//addComponent<LifeComponent>(int(LIFECOMPONENT_H), m, tr, maxLife_);
=======
		addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(55, 40), EnemyHeight_/2, EnemyWidth_/15);
		addComponent<ColDetectorComponent>(int(COLDETECTORCOMPONENT_H), this, player_);



		//addComponent<LifeComponent>(int(LIFECOMPONENT_H), tr, maxLife_);
	}

	void collision() {
		//cout << "colisiona" << endl;
		// animaci�n de ataque y ataque en s�
		// cuando termine la animaci�n se mueve para permitir al jugador escapar
		tr_->setPos(Vector2D(tr_->getPos().getX() + 50, tr_->getPos().getY()));
>>>>>>> Stashed changes:TheFifthElement/src/Entities/EnemyBEU.h
	}

	PlayerBEU* returnPlayer() {
		return player_;
	}
};

