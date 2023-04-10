#include "ProtectionEarthBossComponent.h"
ProtectionEarthBossComponent::ProtectionEarthBossComponent() {

}

void ProtectionEarthBossComponent::initComponent() {
	bossMovement = ent_->getComponent<MovementEarthBossComponent>(MOVEMENTEARTHBOSSCOMPONENT_H);
	animator = ent_->getComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	intervalProtection = SDLUtils::instance()->rand().nextInt(8, 15);
	unsigned timer = clock();
	lastProtectionTime = (double(timer) / CLOCKS_PER_SEC);
}

void ProtectionEarthBossComponent::update() {
	unsigned timer = clock();
	timeExecution = (double(timer) / CLOCKS_PER_SEC);
	if (bossMovement->getBossProtected()) {
		animator->newAnimation(AnimationEarthBossComponent::IdleProtection);
		if (startProtectionTime + 5 < timeExecution) {
			unprotect();
		}
	}
	else if (lastProtectionTime + intervalProtection < timeExecution) {
		protect();
	}
}

void ProtectionEarthBossComponent::protect() {
	animator->newAnimation(AnimationEarthBossComponent::Protection);
	bossMovement->setBossProtected(true);
	unsigned timer = clock();
	startProtectionTime = (double(timer) / CLOCKS_PER_SEC);
}

void ProtectionEarthBossComponent::unprotect() {
	intervalProtection = SDLUtils::instance()->rand().nextInt(8, 15); // Siguiente proteccion en 8 - 15 segundos
	animator->newAnimation(AnimationEarthBossComponent::Protection);
	bossMovement->setBossProtected(false);
	unsigned timer = clock();
	lastProtectionTime = (double(timer) / CLOCKS_PER_SEC);
}