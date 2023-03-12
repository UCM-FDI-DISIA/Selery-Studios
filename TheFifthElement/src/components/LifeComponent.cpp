#include "LifeComponent.h"

LifeComponent::LifeComponent(float maxLife, LifeBar* lifeBar) {
	life_ = maxLife_ = maxLife;
	lifeBar_ = lifeBar;
}

void LifeComponent::initComponent() {
	enemyIm = ent_->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H);
}

void LifeComponent::update() {
	lifeBar_->updatePos();
	cout << life_ << endl;
}

void LifeComponent::subLife(float damage) {
	//life_ -= damage;
	//if (life_ <= 0)
	//{
	//	lifeBar_->setAlive(false);
	//	// llamar a muerte
	//	ent_->Die();
	//}
	//lifeBar_->subLife(life_);
}

void LifeComponent::subLifeDie(float damage) {
	life_ -= damage;
	if (life_ <= 0){
		lifeBar_->setAlive(false);
		playDieSound();
	}
	lifeBar_->subLife(life_);
	playDamageSound();
}

void LifeComponent::render() {
	lifeBar_->renderAll();
}

void LifeComponent::playDamageSound() {
	if (enemyIm == nullptr) { sdlutils().soundEffects().at("playerDamage").play(); }
	else {
		string type = enemyIm->Get_enemy();

		if ("bat") { sdlutils().soundEffects().at("batDamage").play(); }
		else if ("shroom") { sdlutils().soundEffects().at("shroomDamage").play(); }
		else if ("goblin") { sdlutils().soundEffects().at("goblinDamage").play(); }
		else if ("skeleton") { sdlutils().soundEffects().at("skeletonDamage").play(); }
	}
}

void LifeComponent::playDieSound() {
	if (enemyIm == nullptr) { sdlutils().soundEffects().at("playerDie").play(); }
	else {
		string type = enemyIm->Get_enemy();

		if ("bat") { sdlutils().soundEffects().at("batDie").play(); }
		else if ("shroom") { sdlutils().soundEffects().at("shroomDie").play(); }
		else if ("goblin") { sdlutils().soundEffects().at("goblinDie").play(); }
		else if ("skeleton") { sdlutils().soundEffects().at("skeletonDie").play(); }
	}
}