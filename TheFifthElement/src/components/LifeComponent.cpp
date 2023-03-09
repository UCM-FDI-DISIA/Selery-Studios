#include "LifeComponent.h"

LifeComponent::LifeComponent(float maxLife, LifeBar* lifeBar, bool enemy) {
	life_ = maxLife_ = maxLife;
	lifeBar_ = lifeBar;
	enemy_ = enemy;
}

void LifeComponent::initComponent() {
	im_ = ent_->getComponent<Image>(IMAGE_H);
	if (enemy_) {
		anim_ = ent_->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H);
		eMov_ = ent_->getComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H);
	}
	else {

	}
}

void LifeComponent::update() {
	lifeBar_->updatePos();
	//cout << life_ << endl;
	if (die_) {
		if (!im_->isAnimPlaying())
			ent_->setAlive(false);
	}
	else {
		if (!im_->isAnimPlaying()) {
			if (enemy_) {
				if (collision) {

					//animaci�n de ataque y ataque en s�
					anim_->changeState(AnimationEnemyBEUComponent::Attack);
					eMov_->stop(true);
					collision = false;
				}
				else {
					anim_->changeState(AnimationEnemyBEUComponent::Moving);
					eMov_->stop(false);

				}
				if (anim_->currentState_ != AnimationEnemyBEUComponent::Hit)hit = false;
			}
		}
	}
}

void LifeComponent::Death() {
	die_ = true;
	if (enemy_) {// enemy 
		anim_->changeState(AnimationEnemyBEUComponent::Death);
		eMov_->stop(true);
	}
	else {// player

	}
}

void LifeComponent::Hit(float damage)
{
	if (!hit) {
		if (getLife() - damage <= 0)
		{
			subLife(damage);
			Death();
		}
		else {
			subLife(damage);
			if (enemy_) {// enemy
				anim_->changeState(AnimationEnemyBEUComponent::Hit);
				eMov_->stop(true);
			}
			else {// player

			}
		}
		hit = true;
	}

	//en el hit
	// cuando termine la animaci�n se mueve para permitir al jugador escapar
	//tr_->setPos(Vector2D(tr_->getPos().getX() + 50, tr_->getPos().getY()));
}

void LifeComponent::subLife(float damage) {
	life_ -= damage;
	if (life_ <= 0)lifeBar_->setAlive(false);

	lifeBar_->subLife(life_);
}

void LifeComponent::subLifeDie(float damage) {
	life_ -= damage;
	if (life_ <= 0)
	{
		lifeBar_->setAlive(false);
		// llamar a muerte
		//ent_->Die();
	}
	lifeBar_->subLife(life_);
}

void LifeComponent::render() {
	lifeBar_->renderAll();
}
