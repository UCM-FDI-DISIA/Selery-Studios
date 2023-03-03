﻿#include "EnemyBEU.h"
#include "../components/Image.h"

EnemyBEU::~EnemyBEU(){}

EnemyBEU::EnemyBEU(PlayerBEU* player, float maxLife, string enemy, string type) : Entity()
{
	maxLife_ = maxLife;
	life_ = maxLife;
	enemy_ = enemy;
	type_ = type;
	player_ = player;


	float a = 1.0f;
	float lookingRange = 150.0f;
	float lookingWidth = 100.0f;


	anim_ = addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, type_, enemy_);
	anim_->changeState(AnimationEnemyBEUComponent::Moving);
	anim_->updateAnimation();


	//tr_ = addComponent<Transform>(TRANSFORM_H, EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_, speed_, nframes_, matrix_);
	tr_ = addComponent<Transform>(TRANSFORM_H, EnemyPosition_, EnemyWidthQUESISIRVE_, EnemyHeightQUESISIRVE_, EnemyRotation_, speed_, nframes_, matrix_);
	trPlayer_ = player_->getComponent<Transform>(TRANSFORM_H);


	im_ = addComponent<Image>(IMAGE_H, t_, nframes_, nframes_, fila_, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT);

	mov_ = addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	tr_->setDir(Vector2D(1, 0));

	eMov_ = addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player, enemy_);

	col_ = addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, offset_, ColHeight_, ColWidth_);
	addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, this, player_);

	set_ = true;

	//addComponent<LifeComponent>(int(LIFECOMPONENT_H), tr, maxLife_);
}

void EnemyBEU::collision(bool col) {
	if (col) {
		//cout << isAttacking_ << endl;
		if (!im_->isAnimPlaying()) {
			//cout << "colisiona" << endl;
		// animaci�n de ataque y ataque en s�
	//llamar a cambiar estado a attack
			anim_->changeState(AnimationEnemyBEUComponent::Attack);
			//en el hit
			// cuando termine la animaci�n se mueve para permitir al jugador escapar
			//tr_->setPos(Vector2D(tr_->getPos().getX() + 50, tr_->getPos().getY()));
		}
	}
	else {
		if (!im_->isAnimPlaying()) {
			// lógica de recibir daño, muerte o movimiento
			anim_->changeState(AnimationEnemyBEUComponent::Moving);
		}
	}
	
}

PlayerBEU* EnemyBEU::returnPlayer() {
	return player_;
}

void EnemyBEU::setOffset(Vector2D offset) {
	col_->setOffset(offset);
}

void EnemyBEU::setCollider(Vector2D offset, float h, float w)
{
	col_->setCollider(offset, h, w);
}

void EnemyBEU::setColAnim(float EnemyWidth, float EnemyHeight, int nframes, Vector2D offset,
	float ColWidth, float ColHeight, Texture* t, bool Anim)
{
	//EnemyWidth_ = EnemyWidth;
	//EnemyHeight_ = EnemyHeight;
	nframes_ = nframes;
	offset_ = offset;
	ColWidth_ = ColWidth;
	ColHeight_ = ColHeight;
	t_ = t;
	if (set_) {
		im_->setSpriteAnim(Anim, nframes_, 0, t_);
		col_->setCollider(offset_, ColHeight_, ColWidth_);
	}
}


