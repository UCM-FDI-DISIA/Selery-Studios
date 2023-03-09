#include "EnemyBEU.h"
#include "../components/Image.h"

EnemyBEU::~EnemyBEU(){}

EnemyBEU::EnemyBEU(Vector2D pos,PlayerBEU* player, float maxLife, string enemy, string type) : Entity()
{
	maxLife_ = life_ = maxLife;
	enemy_ = enemy;
	type_ = type;
	player_ = player;



	anim_ = addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, type_, enemy_, player_);
	anim_->changeState(AnimationEnemyBEUComponent::Moving);
	anim_->updateAnimation();


	//tr_ = addComponent<Transform>(int(TRANSFORM_H), pos, EnemyWidth_, EnemyHeight_, EnemyRotation_, speed_, nframes_, matrix_);
	//trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
	//tr_ = addComponent<Transform>(TRANSFORM_H, EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_, speed_, nframes_, matrix_);
	tr_ = addComponent<Transform>(TRANSFORM_H, pos, EnemyWidthQUESISIRVE_, EnemyHeightQUESISIRVE_, EnemyRotation_, speed_, nframes_, matrix_);
	trPlayer_ = player_->getComponent<Transform>(TRANSFORM_H);

	nframes_ = anim_->getNFrames();
	t_ = anim_->getTexture();
	
	im_ = addComponent<Image>(IMAGE_H, t_, nframes_, nframes_, fila_, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT);

	mov_ = addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	tr_->setDir(Vector2D(1, 0));

	eMov_ = addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player, enemy_);
	lifeC_ = addComponent<LifeComponent>(LIFECOMPONENT_H, maxLife_, nullptr, true);

	offset_ = anim_->getOffset();
	ColHeight_ = anim_->getColHeight();
	ColWidth_ = anim_->getColWidth();

	col_ = addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, offset_, ColHeight_, ColWidth_);
	addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, this, player_);

	/*addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, this,
		player_->getComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H)->getBox(), 1);*/


}

