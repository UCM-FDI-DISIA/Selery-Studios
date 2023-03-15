#include "AnimationEarthBossComponent.h"
void AnimationEarthBossComponent::initComponent() {
	imBoss = ent_->getComponent<Image>(IMAGE_H);
}

void AnimationEarthBossComponent::newAnimation(Animations newAnim) {
	switch (newAnim)
	{
	case AnimationEarthBossComponent::Idle:
		imBoss->setAnim(true, 0, 8, 0, 100);
		break;
	case AnimationEarthBossComponent::Moving:
		imBoss->setAnim(true, 1, 8, 0, 100);
		break;
	case AnimationEarthBossComponent::Attack:
		imBoss->setAnim(true, 2, 17, 0, 100);
		break;
	case AnimationEarthBossComponent::Hit:
		imBoss->setAnim(true, 3, 12, 0, 100);
		break;
	case AnimationEarthBossComponent::Death:
		imBoss->setAnim(true, 4, 13, 0, 100);
		break;
	case AnimationEarthBossComponent::IdleProtection:
		break;
	case AnimationEarthBossComponent::Protection:
		break;
	}
}