﻿#include "LifeComponent.h"
#include "InputComponentBEU.h"
#include "../states/BeatEmUpState.h"

LifeComponent::LifeComponent(float maxLife) {
	life_ = maxLife_ = maxLife;
}

void LifeComponent::initComponent() {
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	type_ = im_->getType();

	enemy_ = ent_->hasComponent(ANIMATIONENEMYBEUCOMPONENT_H);


	if (enemy_) {
		anim_ = ent_->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H);
		eMov_ = ent_->getComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H);
		entTransform_ = ent_->getComponent<Transform>(TRANSFORM_H);
		barWidth_ = backWidth_ = borderWidth_ = (entTransform_->getW() / 4) * entTransform_->getS();
		barHeight_ = backHeight_ = borderHeight_ = (entTransform_->getH() / 11) * entTransform_->getS();
		pos_ = Vector2D(entTransform_->getPos().getX(), entTransform_->getPos().getY());
	}
	else {
		entTransform_ = ent_->getComponent<Transform>(TRANSFORM_H);
		barWidth_ = backWidth_ = borderWidth_ = 100 * entTransform_->getScale();
		barHeight_ = backHeight_ = borderHeight_ = 30 * entTransform_->getScale();
		skin_ = ent_->getComponent<SkinBEUComponent>(SKINBEUCOMPONENT_H);
	}
	chooseTexture();
}

void LifeComponent::update() {
	if (!set_ && !enemy_) { 
		inp_ = ent_->getComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H); 
		for (int i = 0; i < 4; i++) {
			types[i].life = -1.0f;
			types[i].alive = inp_->elements[i];
		}
		set_ = true;
	}
	
	if(enemy_)pos_ = Vector2D(entTransform_->getPos().getX(), entTransform_->getPos().getY()) - Vector2D(this->mngr_->camRect_.x, this->mngr_->camRect_.y);
	
	if (die_) {
		if (!im_->getIsAnimUnstoppable()) {
			if (enemy_)ent_->setAlive(false);
			else {
				int i = 0;
				while (!types[i].alive && i < 4) i++;

				if (i == 4) {
					ent_->setAlive(false);
					GameManager::instance()->goTopDown();
				}
				else  {
					if (type_ == "air") inp_->setAir(false);// bloquea aire
					else if (type_ == "fire")inp_->setFire(false);// bloquea fuego
					else if (type_ == "water")inp_->setWater(false);// bloquea agua
					else if (type_ == "earth") inp_->setEarth(false);// bloquea tierra

					die_ = false;
					hit_ = false;
				}
			}
		}
	}
	else {
		if (!im_->getIsAnimUnstoppable()) {
		////if (!im_->isAnimPlaying()) {
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
				be->ShakeCam(15);
				if (skin_->currentState_ != SkinBEUComponent::Hit) hit_ = false;
			}
		}
	}
}

void LifeComponent::Death() {
	die_ = true;
	if (enemy_) {// enemy 
		anim_->changeState(AnimationEnemyBEUComponent::Death);
		eMov_->stop(true);
		BeatEmUpState* beatemupstate = static_cast<BeatEmUpState*>(mngr_);
		beatemupstate->finishBEU();
	}
	else {// player
		skin_->changeState(SkinBEUComponent::Death);
		if (type_ == "air") types[0].alive = false;
		else if (type_ == "fire")types[1].alive = false;
		else if (type_ == "water")types[2].alive = false;
		else if (type_ == "earth") types[3].alive = false;
	}
}

void LifeComponent::Hit(float damage) {
	if (!hit_) {
		float realDamage = damage * damageMultiplier_ * damageReduction_;
		if (getLife() - (realDamage) > 0) {
			if (enemy_) {// enemy
				anim_->changeState(AnimationEnemyBEUComponent::Hit);
				//eMov_->moveBackX();
				eMov_->stop(true);
				
				
			}
			else {// player
				be->ShakeCam(15);
				/*inp_->MovePlayerBack();*/
				skin_->changeState(SkinBEUComponent::Hit);
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
	float realDamage = damage * damageMultiplier_ * damageReduction_;
	life_ -= (realDamage);

	if (life_ <= 0) {
		life_ = 0;
		Death();
		if (enemy_) {
			properties().getPowerUpRef()->instancePowerUp();
		}
		else be->ShakeCam(15);
	
	}
	 
	playDamageSound();
	updateLifeBar();
}

void LifeComponent::updateLifeBar() {
	barWidth_ = ((life_ * backWidth_) / maxLife_);
}


void LifeComponent::chageType(float maxLife) {
	if (type_ == "air") {
		types[0].life = life_;
	}
	else if (type_ == "fire") {
		types[1].life = life_;
	}
	else if (type_ == "water") {
		types[2].life = life_;
	}
	else if (type_ == "earth") {
		types[3].life = life_;
	}

	type_ = im_->getType();
	maxLife_ = maxLife;

	if (type_ == "air") {
		if (types[0].life == -1)types[0].life = maxLife; // al cambiar por primera vez seteamos vida máxima
		life_ = types[0].life;
	}
	else if (type_ == "fire") {
		if (types[1].life == -1)types[1].life = maxLife; 
		life_ = types[1].life;
	}
	else if (type_ == "water") {
		if (types[2].life == -1)types[2].life = maxLife;
		life_ = types[2].life;
	}
	else if (type_ == "earth") {
		if (types[3].life == -1)types[3].life = maxLife;
		life_ = types[3].life;
	}
	
	chooseTexture();
	updateLifeBar();
}

void LifeComponent::render() {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = 50;
	src.w = 400;

	SDL_Rect dest;
	if(enemy_){
		dest.x = pos_.getX() + (60*entTransform_->getS());
		dest.y = pos_.getY() + (35*entTransform_->getS());
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
		dest.x = 90 * entTransform_->getScale();
		dest.y = 25 * entTransform_->getScale();
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

	else if (type_ == "air") {
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