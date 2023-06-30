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
		if (selectedIt != j)
		{
			SDL_Rect provRect = handStack;
			provRect.x += j % 10 * 145;
			provRect.y += 50 * (j / 10);
			Texture* provTex = &SDLUtils::instance()->images().at(hand[j]->anverseName);
			provTex->render(provRect);
			hand[j]->pos = provRect;
			font->render(Gm_->getRenderer(), to_string(hand[j]->life), provRect.x + 24, provRect.y + 130, {255,255,255});
		}
		else
		{
			Texture* selectedTex = &SDLUtils::instance()->images().at(selected->anverseName);
			SDL_Rect selectedRect = selected->pos;
			selectedRect.y -= 100;
			selectedTex->render(selectedRect);
			font->render(Gm_->getRenderer(), to_string(hand[j]->life), selectedRect.x + 24, selectedRect.y + 130, { 255,255,255 });
		}
	}
	for (int k = 0; k < table.size(); k++)
	{
		SDL_Rect provRect = tableStack;
		provRect.x += k * tablePlace.w / (table.size() + 1);
		Texture* provTex = &SDLUtils::instance()->images().at(table[k]->anverseName);
		provTex->render(provRect);
		font->render(Gm_->getRenderer(), to_string(table[k]->life), provRect.x + 24, provRect.y + 130, { 255,255,255 });
	}
}

void DeckManagerComponent::handleEvents(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT&&selected==nullptr)
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
					if (clicX >= hand[i]->pos.x && clicX <= (hand[i]->pos.x + hand[i]->pos.w) &&
						clicY >= hand[i]->pos.y && clicY <= (hand[i]->pos.y + hand[i]->pos.h))
					{
						selected=hand[i];
						selectedIt = i;
					}
				}
			}
		}
		if (event.button.button == SDL_BUTTON_LEFT && selected != nullptr)
		{
			int clicX = event.button.x;
			int clicY = event.button.y;
			if (clicX >= tablePlace.x && clicX <= (tablePlace.x + tablePlace.w) &&
				clicY >= tablePlace.y && clicY <= (tablePlace.y + tablePlace.h)) 
			{
				if (energy - selected->energy >= 0)
				{
					table.push_back(selected);
					hand.erase(hand.begin() + selectedIt);
					energy -= selected->energy;
					selected = nullptr;
					selectedIt = -1;
				}
				else
				{
					selected = nullptr;
					selectedIt = -1;
				}
			}
		}
		if (event.button.button == SDL_BUTTON_RIGHT)
		{
			selected = nullptr; selectedIt = -1;
		}
	}
}

void DeckManagerComponent::reviewCards()
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i]->life <= 0) { table.erase(table.begin() + i); }
	}
}

void DeckManagerComponent::addTableTurn()
{
	for (int i = 0; i < table.size(); i++)
	{
		table[i]->numTableTurns++;
		table[i]->attacked = false;
	}
}