#include "DeckManagerComponent.h"
#include "../states/CardGameState.h"

void DeckManagerComponent::drawCard(int numCards)
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

void DeckManagerComponent::endTurn() //para una linea de codigo la podria haber saltado y metido dentro del event directamente
{
	static_cast<CardGameState*>(mngr_)->nextTurn();
}

void DeckManagerComponent::render()
{
	for (int i = 0; i < deck.size(); i++)
	{
		deck[i]->reverse->render(deckStack);
	}
	font->render(Gm_->getRenderer(), to_string(deck.size()), deckStack.x + 35, deckStack.y+110, { 255,255,255 });
	
	for (int j = 0; j < hand.size(); j++)
	{
		SDL_Rect provRect = handStack;
		provRect.x += j%10 * 145;
		provRect.y += 50 * (j / 10);
		Texture* provTex = &SDLUtils::instance()->images().at(hand[j]->anverseName);
		provTex->render(provRect);
	}
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