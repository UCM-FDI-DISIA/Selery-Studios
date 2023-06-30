#include "CardPlayerLifeComponent.h"
#include "../states/CardGameState.h"

void CardPlayerLifeComponent::damage(int attack)
{
	life -= attack;
	if (life <= 0)
	{
		static_cast<CardGameState*>(mngr_)->endMatch(ent_);
	}
}