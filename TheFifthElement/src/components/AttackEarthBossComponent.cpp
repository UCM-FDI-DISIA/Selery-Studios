#include "AttackEarthBossComponent.h"
AttackEarthBossComponent::AttackEarthBossComponent() {

}

void AttackEarthBossComponent::initComponent() {
	bossMovement = ent_->getComponent<MovementEarthBossComponent>(MOVEMENTEARTHBOSSCOMPONENT_H);
	animator = ent_->getComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
}

void AttackEarthBossComponent::update() {
	if (bossMovement->getAttack()) {
		animator->newAnimation(AnimationEarthBossComponent::Attack);
	}
}