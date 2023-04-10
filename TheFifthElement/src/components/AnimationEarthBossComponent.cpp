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
		break;
	case Moving:
		if (stage == 1) imBoss->setAnim("GolemFase1_run", 8, false);
		else if (stage == 2) imBoss->setAnim("GolemFase2_run", 8, false);
		break;
	case Attack:
		if (stage == 1) imBoss->setAnim("GolemFase1_attack", 17, false);
		else if (stage == 2) imBoss->setAnim("GolemFase2_attack", 17, false);
		break;
	case Hit:
		if (stage == 1) imBoss->setAnim("GolemFase1_hit", 12, true);
		else if (stage == 2) imBoss->setAnim("GolemFase2_hit", 12, false);
		break;
	case Death:
		if (stage == 1) imBoss->setAnim("GolemFase1_death", 13, true);
		else if (stage == 2) imBoss->setAnim("GolemFase2_death", 13, false);
		break;
	case IdleProtection:
		break;
	case Protection:
		break;
	}
	currentAnimation = newAnim;
}

void AnimationEarthBossComponent::update() {

}