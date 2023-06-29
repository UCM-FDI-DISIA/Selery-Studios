#include "IADeckComponent.h"
#include "../states/CardGameState.h"

void IADeckComponent::drawCard(int numCards)
{
	if (deck.size() > 0)
	{
		for (int i = 0; i < numCards; i++)
		{
			hand.push_back(deck[0]);
			deck.erase(deck.begin());
		}
	}
}

void IADeckComponent::endTurn() //para una linea de codigo la podria haber saltado y metido dentro del event directamente
{
	static_cast<CardGameState*>(mngr_)->nextTurn();
}

void IADeckComponent::render()
{
	for (int i = 0; i < deck.size(); i++)
	{
		deck[i]->reverse->render(deckStack);
	}
	font->render(Gm_->getRenderer(), to_string(deck.size()), deckStack.x + 35, deckStack.y + 110, { 255,255,255 });

	for (int j = 0; j < hand.size(); j++)
	{
		SDL_Rect provRect = handStack;
		provRect.x += j % 10 * 145;
		provRect.y += 50 * (j / 10);
		hand[j]->reverse->render(provRect);
	}
	//for para las cartas en la mesa
}