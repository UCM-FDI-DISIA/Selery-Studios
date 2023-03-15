#include "LifeComponent.h"

LifeComponent::LifeComponent(float maxLife, bool enemy,string type, Entity* ent) {
	life_ = maxLife_ = maxLife;
	enemy_ = enemy;
	type_ = type;
	scale = WIN_WIDTH / 900;
	if (enemy_) {
		entTransform_ = ent->getComponent<Transform>(TRANSFORM_H);
		barWidth_ = backWidth_ = borderWidth_ = (entTransform_->getW() / 4)*scale;
		barHeight_ = backHeight_ = borderHeight_ = (entTransform_->getH() / 11)*scale;
		pos_ = Vector2D(entTransform_->getPos().getX(), entTransform_->getPos().getY());
	}
	else {
		barWidth_ = backWidth_ = borderWidth_ = 300 * scale;
		barHeight_ = backHeight_ = borderHeight_ = 50 * scale;
	}
	chooseTexture();

	for (int i = 0; i < 4; i++) types[i] = -1.0f;
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
	if(enemy_)pos_ = Vector2D(entTransform_->getPos().getX(), entTransform_->getPos().getY()) - Vector2D(this->mngr_->camRect_.x, this->mngr_->camRect_.y);
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
				if (anim_->currentState_ != AnimationEnemyBEUComponent::Hit) hit_ = false;
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

void LifeComponent::chageType(string type, float maxLife) {
	if (type_ == "fire") types[0] = life_;
	else if (type_ == "wind")types[1] = life_;
	else if (type_ == "water")types[2] = life_;
	else if (type_ == "earth")types[3] = life_;
	
	type_ = type;
	maxLife_ = maxLife;

	if (type_ == "fire") {
		if (types[0] == -1)types[0] = maxLife;
		life_ = types[0];
	}
	else if (type_ == "wind") {
		if (types[1] == -1)types[1] = maxLife;
		life_ = types[1];
	}
	else if (type_ == "water") {
		if (types[2] == -1)types[2] = maxLife;
		life_ = types[2];
	}
	else if (type_ == "earth") {
		if (types[3] == -1)types[3] = maxLife;
		life_ = types[3];
	}
	
	chooseTexture();
	barWidth_ = ((life_ * backWidth_) / maxLife_);

}

void LifeComponent::render() {
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = 50;
		src.w = 400;

		SDL_Rect dest;
	if(enemy_){
		dest.x = pos_.getX() + (60*scale);
		dest.y = pos_.getY() + (35*scale);
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
	else {
		dest.x = 100*scale;
		dest.y = 35*scale;
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