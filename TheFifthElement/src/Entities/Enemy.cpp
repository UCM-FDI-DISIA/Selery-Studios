//#include "Enemy.h"
//Enemy::Enemy(PlayerTD* player, float maxLife) : Entity()
//{
//	addComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H);
//	maxLife_ = maxLife;
//	life_ = maxLife;
//	float a = -1.0f;
//	float lookingRange = 150.0f;
//	float lookingWidth = 100.0f;
//	tr = addComponent<Transform>(TRANSFORM_H, EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_, speed_, nframes, matrix_);
//	t = &SDLUtils::instance()->images().at("TD_wind_mushroom");
//	player_ = player;
//	trPlayer_ = player_->getComponent<Transform>(TRANSFORM_H);
//	//addComponent<LifeComponent>(int(LIFECOMPONENT_H), m, tr, maxLife_);
//	ch = addComponent<CheckCollision>(CHECKCOLLISION_H, player_, lookingRange, lookingWidth, a);
//	fila_ = 0;
//	addComponent<Image>(IMAGE_H, t, nframes, nframes, fila_, ENEMYTD_WIDTH, ENEMYTD_HEIGHT);
//	addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), EnemyHeight_, EnemyWidth_ / 7);
//	addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
//
//}