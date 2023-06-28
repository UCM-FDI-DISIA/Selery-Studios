#include "DeckManagerComponent.h"
#include "../states/CardGameState.h"

void DeckManagerComponent::drawCard(int numCards)
{
	for (int i = 0; i < numCards; i++)
	{
		hand.push_back(deck[1]);
		deck.erase(deck.begin());
	}
}

void DeckManagerComponent::endTurn() //para una linea de codigo la podria haber saltado y metido dentro del event directamente
{
	static_cast<CardGameState*>(mngr_)->nextTurn();
}

void DeckManagerComponent::render()
{
	//for para las cartas de deck
	//for para las cartas en mano
	//for para las cartas en la mesa
}

void DeckManagerComponent::handleEvents(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			int clicX = event.button.x;
			int clicY = event.button.y;

			if (clicX >= endTurnButtonRect.x && clicX <= (endTurnButtonRect.x + endTurnButtonRect.w) &&
				clicY >= endTurnButtonRect.y && clicY <= (endTurnButtonRect.y + endTurnButtonRect.h)) //click para acabar el turno
			{
				endTurn();
			}
			else
			{
				for (int i = 0; i < hand.size(); i++)
				{
					//if ()
				}
			}
		}

	}
}