#include "LifeEarthBossComponent.h"
LifeEarthBossComponent::LifeEarthBossComponent() {
	maxLife = 100;
	life = maxLife;
}
void LifeEarthBossComponent::receiveDamage(float damage, float mul) {
	life -= damage * mul;
	if (life <= 0) {
		ent_->setAlive(false);
	}
	cout << "Recibi dano";
}