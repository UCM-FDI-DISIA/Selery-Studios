#pragma once
#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "../GameManager.h"
#include "../components/CheckCollision.h"
#include "PlayerBEU.h"
#include "../components/LifeComponent.h"
#include "../components/MovementComponent.h"
#include "../components/EnemyBEUDirectionComponent.h"
#include "../../ColliderComponent.h"
#include "../../ColDetectorComponent.h"

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
	CheckCollision* ch;
	MovementComponent* mov_;
	EnemyBEUDirectionComponent* eMov_;
	ColliderComponent* col_;
#pragma endregion

#pragma region parameters
	float speed_ = 1.0f;
#pragma endregion

#pragma region sprites
	string enemy_, type_;
	float EnemyWidth_, EnemyHeight_, EnemyRotation_ = 1;
	int nframes;
	int fila_ = 0;
	float life_, maxLife_;
	bool matrix_ = false;

	Vector2D offset_;
	float ColWidth_, ColHeight;
#pragma endregion


public:



	~EnemyBEU()
	{

	}

	EnemyBEU(PlayerBEU* player, float maxLife, string enemy, string type) : Entity()
	{
		maxLife_ = maxLife;
		life_ = maxLife;
		enemy_ = enemy;
		type_ = type;
		player_ = player;


		float a = 1.0f;
		float lookingRange = 150.0f;
		float lookingWidth = 100.0f;


		setTexture();


		tr_ = addComponent<Transform>(int(TRANSFORM_H), EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_,speed_, nframes, matrix_);
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));


		addComponent<Image>(int(IMAGE_H), t_, nframes, nframes, fila_);

		cmpId_type s = int(MOVEMENTCOMPONENT_H);
		mov_ = addComponent<MovementComponent>(s);

		cmpId_type e = int(ENEMYBEUDIRECTIONCOMPONENT_H);
		eMov_ = addComponent<EnemyBEUDirectionComponent>(e, player, enemy_);

		col_ = addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), offset_, ColHeight, ColWidth_);
		addComponent<ColDetectorComponent>(int(COLDETECTORCOMPONENT_H), this, player_);



		//addComponent<LifeComponent>(int(LIFECOMPONENT_H), tr, maxLife_);
	}

	void collision() {
		//cout << "colisiona" << endl;
		// animaci�n de ataque y ataque en s�
		// crear un booleano que no permita seguir haciendo daño al personaje
		// mientras se realice la animación de ataque/ataque
		// cuando termine la animaci�n se mueve para permitir al jugador escapar
		tr_->setPos(Vector2D(tr_->getPos().getX() + 50, tr_->getPos().getY()));
	}

	PlayerBEU* returnPlayer() {
		return player_;
	}

	void setTexture() {
		if (enemy_ == "shroom") {

			nframes = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 55);
			ColHeight = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Mushroom_run");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Mushroom_run");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Mushroom_run");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Mushroom_run");
			}
		}

		else if (enemy_ == "skeleton") {

			nframes = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 40);
			ColHeight = EnemyHeight_ / 2;
			ColWidth_ = EnemyWidth_ / 15;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Skeleton_run");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Skeleton_run");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Skeleton_run");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Skeleton_run");
			}
		}

		else if (enemy_ == "goblin") {

			nframes = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 55);
			ColHeight = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Goblin_run");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Goblin_run");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Goblin_run");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Goblin_run");
			}
		}

		else if (enemy_ == "bat") {

			nframes = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 50);
			ColHeight = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Bat_fly");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Bat_fly");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Bat_fly");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Bat_fly");
			}
		}
	}

	void setOffset(Vector2D offset) {
		col_->setOffset(offset);
	}
};

