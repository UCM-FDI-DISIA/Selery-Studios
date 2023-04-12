#include "AttackLightBossComponent.h"

AttackLightBossComponent::AttackLightBossComponent()
{
	fightState = 1;
}

void AttackLightBossComponent::initComponent()
{

}

void AttackLightBossComponent::setState(int state)
{
	fightState = state;
}