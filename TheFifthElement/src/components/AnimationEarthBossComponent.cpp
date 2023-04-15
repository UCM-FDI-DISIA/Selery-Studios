#include "AnimationEarthBossComponent.h"
void AnimationEarthBossComponent::initComponent() {
	imBoss = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	stage = 1;
}

void AnimationEarthBossComponent::newAnimation(Animations newAnim) {
	switch (newAnim)
	{
	case Idle:
		if (stage == 1) imBoss->setAnim("GolemFase1_idle", 8, false);
		else if (stage == 2) imBoss->setAnim("GolemFase2_idle", 8, false);
		else if (stage == 3) imBoss->setAnim("Moose_idle", 8, false);
		break;
	case Moving:
		if (stage == 1) imBoss->setAnim("GolemFase1_run", 8, false);
		else if (stage == 2) imBoss->setAnim("GolemFase2_run", 8, false);
		else if (stage == 3) imBoss->setAnim("Moose_run", 8, false);
		break;
	case Attack:
		if (stage == 1) imBoss->setAnim("GolemFase1_attack", 17, true);
		else if (stage == 2) imBoss->setAnim("GolemFase2_attack", 17, true);
		else if (stage == 3) imBoss->setAnim("Moose_attack", 30, true);
		break;
	case Hit:
		if (stage == 1) imBoss->setAnim("GolemFase1_hit", 12, true);
		else if (stage == 2) imBoss->setAnim("GolemFase2_hit", 12, true);
		else if (stage == 3) imBoss->setAnim("Moose_hit", 6, true);
		break;
	case Death:
		if (stage == 1) imBoss->setAnim("GolemFase1_death", 13, true);
		else if (stage == 2) imBoss->setAnim("GolemFase2_death", 13, true);
		else if (stage == 3) imBoss->setAnim("Moose_death", 15, true);
		break;
	case IdleProtection:
		if (stage == 2) imBoss->setAnim("GolemFase2_idleProtection", 8, true);
		break;
	case Protection:
		if (stage == 2) imBoss->setAnim("GolemFase2_protection", 10, true);
		break;
	}
	currentAnimation = newAnim;
}

void AnimationEarthBossComponent::update() {

}