#include "DeckManagerComponent.h"
#include "../states/CardGameState.h"

void DeckManagerComponent::drawCard(int numcCards)
{
	
}

void DeckManagerComponent::endTurn()
{
	static_cast<CardGameState*>(mngr_)->nextTurn();
}