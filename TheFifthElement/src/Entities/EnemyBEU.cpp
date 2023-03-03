#include "EnemyBEU.h"
#include "../components/Image.h"

EnemyBEU::~EnemyBEU(){}

EnemyBEU::EnemyBEU(Vector2D pos,PlayerBEU* player, float maxLife, string enemy, string type) : Entity()
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


	tr_ = addComponent<Transform>(int(TRANSFORM_H), pos, EnemyWidth_, EnemyHeight_, EnemyRotation_, speed_, nframes_, matrix_);
	trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));


	im_ = addComponent<Image>(int(IMAGE_H), t_, nframes_, nframes_, fila_);

	cmpId_type s = int(MOVEMENTCOMPONENT_H);
	mov_ = addComponent<MovementComponent>(s);
	tr_->setDir(Vector2D(1, 0));

	cmpId_type e = int(ENEMYBEUDIRECTIONCOMPONENT_H);
	eMov_ = addComponent<EnemyBEUDirectionComponent>(e, player, enemy_);

	col_ = addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), offset_, ColHeight_, ColWidth_);
	addComponent<ColDetectorComponent>(int(COLDETECTORCOMPONENT_H), this, player_);

	set_ = true;

	//addComponent<LifeComponent>(int(LIFECOMPONENT_H), tr, maxLife_);
}

void EnemyBEU::collision() {
	//cout << isAttacking_ << endl;
	if (!im_->isAnimPlaying()) {
		//cout << "colisiona" << endl;
	// animaci�n de ataque y ataque en s�
//llamar a cambiar estado a attack
		anim_->changeState(AnimationEnemyBEUComponent::Attack);
		//en el hit
		// cuando termine la animaci�n se mueve para permitir al jugador escapar
		//tr_->setPos(Vector2D(tr_->getPos().getX() + 50, tr_->getPos().getY()));
		isAttacking_ = true;
	}
}

void EnemyBEU::noCollision() {
	if (!im_->isAnimPlaying()) {
		// lógica de recibir daño, muerte o movimiento
		anim_->changeState(AnimationEnemyBEUComponent::Moving);
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
	EnemyWidth_ = EnemyWidth;
	EnemyHeight_ = EnemyHeight;
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

void EnemyBEU::setAttackBool(bool s)
{
	isAttacking_ = s;
}


