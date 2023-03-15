#include "LifeEarthBossComponent.h"
LifeEarthBossComponent::LifeEarthBossComponent() {
	maxLife = 3000;
	life = maxLife;
}

void LifeEarthBossComponent::initComponent() {
	animEarthBoss = ent_->getComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
}
void LifeEarthBossComponent::receiveDamage(float damage, float mul) {
	life -= damage * mul;
	animEarthBoss->newAnimation(AnimationEarthBossComponent::Animations::Hit);
	if (life <= 0) {
		ent_->setAlive(false);
	}
	cout << "Recibi dano";
}