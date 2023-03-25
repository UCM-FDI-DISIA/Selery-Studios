#include "AnimationEarthBossComponent.h"
void AnimationEarthBossComponent::initComponent() {
	imBoss = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
}

void AnimationEarthBossComponent::newAnimation(Animations newAnim) {
	switch (newAnim)
	{
	case Idle:
		imBoss->setAnim("GolemFase1_idle", 8, false);
		break;
	case Moving:
		imBoss->setAnim("GolemFase1_run", 8, false);
		break;
	case Attack:
		imBoss->setAnim("GolemFase1_attack", 17, true);
		break;
	case Hit:
		imBoss->setAnim("GolemFase1_hit", 12, true);
		break;
	case Death:
		imBoss->setAnim("GolemFase1_death", 13, true);
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