#include "LifeComponent.h"

LifeComponent::LifeComponent(float maxLife, bool enemy,string type, Entity* ent) {
	life_ = maxLife_ = maxLife;
	enemy_ = enemy;
	type_ = type;
	entTransform_ = ent->getComponent<Transform>(TRANSFORM_H);
	barWidth_ = backWidth_ = borderWidth_ = entTransform_->getW() / 4;
	barHeight_ = backHeight_ = borderHeight_ = entTransform_->getH() / 11;
	chooseTexture();
	pos_ = entTransform_->getPos();
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
	pos_ = entTransform_->getPos() - Vector2D(this->mngr_->camRect_.x, this->mngr_->camRect_.y);
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
				if (anim_->currentState_ != AnimationEnemyBEUComponent::Hit)hit_ = false;
			}
			else {//player

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
	if (!hit_) {
		if (getLife() - damage > 0) {
			if (enemy_) {// enemy
				anim_->changeState(AnimationEnemyBEUComponent::Hit);
				eMov_->stop(true);
			}
			else {// player

			}
		}
		subLife(damage);
		hit_ = true;
	}

	//en el hit
	// cuando termine la animaci�n se mueve para permitir al jugador escapar
	//tr_->setPos(Vector2D(tr_->getPos().getX() + 50, tr_->getPos().getY()));
}

void LifeComponent::subLife(float damage) {
	life_ -= damage;
	if (life_ <= 0)
	{
		life_ = 0;
		Death();
	}
	playDamageSound();
	barWidth_ = ((life_ * backWidth_) / maxLife_);
}

void LifeComponent::render() {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = 50;
	src.w = 400;

	SDL_Rect dest;

	dest.x = pos_.getX() + 55;
	dest.y = pos_.getY() + 35;
	dest.h = backHeight_;
	dest.w = backWidth_;
	backTexture_->render(src, dest);


	dest.h = barHeight_;
	dest.w = barWidth_;
	barTexture_->render(src, dest);


	dest.h = borderHeight_;
	dest.w = borderWidth_;
	borderTexture_->render(src, dest);
}

void LifeComponent::chooseTexture() {
	if (type_ == "fire") {
		barTexture_ = &SDLUtils::instance()->images().at("Fire_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Fire_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Fire_LifeBarBorder");
	}

	else if (type_ == "wind") {
		barTexture_ = &SDLUtils::instance()->images().at("Air_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Air_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Air_LifeBarBorder");
	}

	else if (type_ == "water") {
		barTexture_ = &SDLUtils::instance()->images().at("Water_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBorder");
	}

	else if (type_ == "earth") {
		barTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBorder");
	}
}

void LifeComponent::playDamageSound() {
	if (!enemy_) { sdlutils().soundEffects().at("playerDamage").play(); }
	else {
		string type = anim_->getEnemy();

		if (type == "bat") { sdlutils().soundEffects().at("batDamage").play(); }
		else if (type == "shroom") { sdlutils().soundEffects().at("shroomDamage").play(); }
		else if (type == "goblin") { sdlutils().soundEffects().at("goblinDamage").play(); }
		else if (type == "skeleton") { sdlutils().soundEffects().at("skeletonDamage").play(); }
	}
}

void LifeComponent::playDieSound() {
	if (!enemy_) { sdlutils().soundEffects().at("playerDie").play(); }
	else {
		string type = anim_->getEnemy();

		if (type == "bat") { sdlutils().soundEffects().at("batDie").play(); }
		else if (type == "shroom") { sdlutils().soundEffects().at("shroomDie").play(); }
		else if (type == "goblin") { sdlutils().soundEffects().at("goblinDie").play(); }
		else if (type == "skeleton") { sdlutils().soundEffects().at("skeletonDie").play(); }
	}
}