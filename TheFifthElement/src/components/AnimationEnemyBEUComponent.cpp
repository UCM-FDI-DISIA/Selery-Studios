#include "AnimationEnemyBEUComponent.h"

void AnimationEnemyBEUComponent::update() {

	if (currentState_ != nextState_) updateAnimation();
	else updateAn();
}

void AnimationEnemyBEUComponent::changeState(AnimationStates newState)
{
	nextState_ = newState;// as� se evita que se a�ada el mismo estado m�s de una vez
}

void AnimationEnemyBEUComponent::initComponent() {
	t_ = "BEU_air_Mushroom_run";
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	col_ = ent_->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
	playerTr_ = player_->getComponent<Transform>(TRANSFORM_H);
	playerCol_ = player_->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
}
void AnimationEnemyBEUComponent::updateAn() {
	switch (currentState_)
	{
	case AnimationEnemyBEUComponent::Moving:
		if (tr_->getDir().getX() <= 0) {
			im_->setFlip(SDL_FLIP_HORIZONTAL);
		}
		else {
			im_->setFlip(SDL_FLIP_NONE);
		}

		break;
	case AnimationEnemyBEUComponent::Attack:
		posX = tr_->getPos().getX() + col_->getOffset().getX() + col_->getColWidth();
		playerPosX = playerTr_->getPos().getX() + playerCol_->getOffset().getX() + playerCol_->getColWidth() / 2;
		if (posX <= playerPosX) {
			im_->setFlip(SDL_FLIP_NONE);
			if (enemy_ == "shroom")col_->setOffset(Vector2D(65, 55));
		}
		else {
			im_->setFlip(SDL_FLIP_HORIZONTAL);
			if (enemy_ == "shroom")col_->setOffset(Vector2D(55, 55));
		}
		break;
	case AnimationEnemyBEUComponent::Hit:
		break;
	case AnimationEnemyBEUComponent::Death:
		break;
	default:
		break;
	}
}

void AnimationEnemyBEUComponent::updateAnimation() {

	currentState_ = nextState_;

	switch (currentState_)
	{
	case AnimationEnemyBEUComponent::Moving:
		setMovTexture();
		////im_->setSpriteAnim(false, nframes_, 0, t_);
		im_->setAnim(t_, nframes_, false);
		col_->setCollider(offset_, ColHeight_, ColWidth_);
		break;
	case AnimationEnemyBEUComponent::Attack:
		setAttackTexture();
		////im_->setSpriteAnim(true, nframes_, 0, t_);
		im_->setAnim(t_, nframes_, true);
		col_->setCollider(offset_, ColHeight_, ColWidth_);
		break;
	case AnimationEnemyBEUComponent::Hit:
		setHitTexture();
		////im_->setSpriteAnim(true, nframes_, 0, t_);
		im_->setAnim(t_, nframes_, true);
		col_->setCollider(offset_, ColHeight_, ColWidth_);
		break;
	case AnimationEnemyBEUComponent::Death:
		setDeathTexture();
		////im_->setSpriteAnim(true, nframes_, 0, t_);
		im_->setAnim(t_, nframes_, true);
		col_->setCollider(offset_, ColHeight_, ColWidth_);
		break;
	case AnimationEnemyBEUComponent::Idle:
		setIdleTexture();
		////im_->setSpriteAnim(true, nframes_, 0, t_);
		im_->setAnim(t_, nframes_, true);
		col_->setCollider(offset_, ColHeight_, ColWidth_);
		break;
	default:
		break;
	}
	
}

void AnimationEnemyBEUComponent::setMovTexture() {
	if (enemy_ == "shroom") {

		nframes_ = 4;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(60, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 3;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Mushroom_run";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Mushroom_run";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Mushroom_run";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Mushroom_run";
		}
	}

	else if (enemy_ == "skeleton") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(60, 45);
		ColHeight_ = 3 * ENEMYBEU_HEIGHT / 7;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Skeleton_run";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Skeleton_run";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Skeleton_run";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Skeleton_run";
		}
	}

	else if (enemy_ == "goblin") {

		nframes_ = 4;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 3;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Goblin_run";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Goblin_run";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Goblin_run";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Goblin_run";
		}
	}

	else if (enemy_ == "bat") {

		nframes_ = 8;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 4;
		ColWidth_ = ENEMYBEU_WIDTH / 4;

		if (type_ == "fire") {
			t_ = "BEU_fire_Bat_fly";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Bat_fly";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Bat_fly";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Bat_fly";
		}
	}
}

void AnimationEnemyBEUComponent::setAttackTexture() {
	if (enemy_ == "shroom") {

		nframes_ = 8;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(65, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 3;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Mushroom_attack";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Mushroom_attack";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Mushroom_attack";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Mushroom_attack";
		}
	}

	else if (enemy_ == "skeleton") {

		nframes_ = 8;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55,42);
		ColHeight_ = 2.5 * ENEMYBEU_HEIGHT / 6;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Skeleton_attack";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Skeleton_attack";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Skeleton_attack";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Skeleton_attack";
		}
	}

	else if (enemy_ == "goblin") {

		nframes_ = 8;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(65, 80);
		ColHeight_ = ENEMYBEU_HEIGHT / 5;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Goblin_attack";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Goblin_attack";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Goblin_attack";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Goblin_attack";
		}
	}

	else if (enemy_ == "bat") {

		nframes_ = 8;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 65);
		ColHeight_ = ENEMYBEU_HEIGHT / 6;
		ColWidth_ = ENEMYBEU_WIDTH / 4;

		if (type_ == "fire") {
			t_ = "BEU_fire_Bat_attack";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Bat_attack";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Bat_attack";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Bat_attack";
		}
	}
}

void AnimationEnemyBEUComponent::setHitTexture()
{
	if (enemy_ == "shroom") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(65, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 3;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Mushroom_hit";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Mushroom_hit";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Mushroom_hit";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Mushroom_hit";
		}
	}

	else if (enemy_ == "skeleton") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 42);
		ColHeight_ = 2.5 * ENEMYBEU_HEIGHT / 6;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Skeleton_hit";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Skeleton_hit";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Skeleton_hit";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Skeleton_hit";
		}
	}

	else if (enemy_ == "goblin") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(65, 80);
		ColHeight_ = ENEMYBEU_HEIGHT / 5;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Goblin_hit";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Goblin_hit";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Goblin_hit";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Goblin_hit";
		}
	}

	else if (enemy_ == "bat") {

		nframes_ = 4;
		EnemyWidth_ = 545;
		EnemyHeight_ = 126;

		offset_ = Vector2D(55, 65);
		ColHeight_ = ENEMYBEU_HEIGHT / 6;
		ColWidth_ = ENEMYBEU_WIDTH / 4;

		if (type_ == "fire") {
			t_ = "BEU_fire_Bat_hit";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Bat_hit";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Bat_hit";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Bat_hit";
		}
	}
}

void AnimationEnemyBEUComponent::setDeathTexture()
{
	if (enemy_ == "shroom") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(60, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 3;
		ColWidth_ = ENEMYBEU_WIDTH / 25;

		if (type_ == "fire") {
			t_ = "BEU_fire_Mushroom_death";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Mushroom_death";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Mushroom_death";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Mushroom_death";
		}
	}

	else if (enemy_ == "skeleton") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 70);
		ColHeight_ = ENEMYBEU_HEIGHT / 4;
		ColWidth_ = ENEMYBEU_WIDTH / 15;

		if (type_ == "fire") {
			t_ = "BEU_fire_Skeleton_death";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Skeleton_death";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Skeleton_death";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Skeleton_death";
		}
	}

	else if (enemy_ == "goblin") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(40, 75);
		ColHeight_ = ENEMYBEU_HEIGHT / 5;
		ColWidth_ = ENEMYBEU_WIDTH / 12;

		if (type_ == "fire") {
			t_ = "BEU_fire_Goblin_death";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Goblin_death";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Goblin_death";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Goblin_death";
		}
	}

	else if (enemy_ == "bat") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(50, 75);
		ColHeight_ = ENEMYBEU_HEIGHT / 6;
		ColWidth_ = ENEMYBEU_WIDTH / 12;

		if (type_ == "fire") {
			t_ = "BEU_fire_Bat_death";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Bat_death";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Bat_death";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Bat_death";
		}
	}
}

void AnimationEnemyBEUComponent::setIdleTexture()
{
	if (enemy_ == "shroom") {

		nframes_ = 4;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(60, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 3;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Mushroom_idle";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Mushroom_idle";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Mushroom_idle";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Mushroom_idle";
		}
	}

	else if (enemy_ == "skeleton") {

		nframes_ = 4;
		EnemyWidth_ = 600;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 42);
		ColHeight_ = 2.5 * ENEMYBEU_HEIGHT / 6;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Skeleton_idle";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Skeleton_idle";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Skeleton_idle";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Skeleton_idle";
		}
	}

	else if (enemy_ == "goblin") {

		nframes_ = 4;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 3;
		ColWidth_ = ENEMYBEU_WIDTH / 5;

		if (type_ == "fire") {
			t_ = "BEU_fire_Goblin_idle";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Goblin_idle";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Goblin_idle";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Goblin_idle";
		}
	}

	else if (enemy_ == "bat") {

		nframes_ = 8;
		EnemyWidth_ = 1200;
		EnemyHeight_ = 150;

		offset_ = Vector2D(55, 55);
		ColHeight_ = ENEMYBEU_HEIGHT / 4;
		ColWidth_ = ENEMYBEU_WIDTH / 4;

		if (type_ == "fire") {
			t_ = "BEU_fire_Bat_fly";
		}

		else if (type_ == "air") {
			t_ = "BEU_air_Bat_fly";
		}

		else if (type_ == "water") {
			t_ = "BEU_water_Bat_fly";
		}

		else if (type_ == "earth") {
			t_ = "BEU_earth_Bat_fly";
		}
	}
}
