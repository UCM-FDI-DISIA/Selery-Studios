#include "LifeComponent.h"

LifeComponent::LifeComponent(float maxLife, LifeBar* lifeBar) {
	life_ = maxLife_ = maxLife;
	lifeBar_ = lifeBar;
}

void LifeComponent::update() {
	lifeBar_->updatePos();
}

void LifeComponent::subLife(float damage) {
	life_ -= damage;
	if (life_ <= 0)
	{
		lifeBar_->setAlive(false);
		// llamar a muerte
		ent_->Die();
	}
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
