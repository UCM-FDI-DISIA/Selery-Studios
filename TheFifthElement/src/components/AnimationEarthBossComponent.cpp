#include "AnimationEarthBossComponent.h"
void AnimationEarthBossComponent::initComponent() {
	imBoss = ent_->getComponent<Image>(IMAGE_H);
}

void AnimationEarthBossComponent::newAnimation(Animations newAnim) {
	switch (newAnim)
	{
	case Idle:
		imBoss->setAnim(false, 0, 8, 0, 100);
		break;
	case Moving:
		imBoss->setAnim(false, 1, 8, 0, 100);
		break;
	case Attack:
		imBoss->setAnim(true, 2, 17, 0, 100);
		break;
	case Hit:
		imBoss->setAnim(true, 3, 12, 0, 100);
		break;
	case Death:
		imBoss->setAnim(true, 4, 13, 0, 100);
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