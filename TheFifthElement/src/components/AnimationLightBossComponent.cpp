#include "AnimationLightBossComponent.h"
#include "../states//BeatEmUpState.h"


void AnimationLightBossComponent::initComponent()
{
	imBoss_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
}

void AnimationLightBossComponent::newAnim(Animations anim)
{
	switch (anim)
	{
	case Idle: imBoss_->setAnim("BEULightBossIdle", 12, false); break;
	case Attack: imBoss_->setAnim("BEULightBossAttackSphere", 15, true); break;
	case Attack2: imBoss_->setAnim("BEULightBossSpecialAttack", 17, true); break;
	case Hit: imBoss_->setAnim("BEULightBossTakeHit", 6, true); break;
	case Die: imBoss_->setAnim("BEULightBossDie", 19, true); break;
	}
	currentAnim = anim;
}

void AnimationLightBossComponent::update()
{
	if (!imBoss_->getIsAnimUnstoppable() && currentAnim != Idle && !dead)
	{
		newAnim(Idle);
	}

	if (dead)
	{
		newAnim(Die);
		if (imBoss_->getIsAnimUnstoppable())
		{
			static_cast<BeatEmUpState*>(mngr_)->finishBEU();
		}
	}
}