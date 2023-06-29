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
	for (int k = 0; k < table.size(); k++)
	{
		SDL_Rect provRect = tableStack;
		provRect.x += k * tablePlace.w / (table.size() + 1);
		Texture* provTex = &SDLUtils::instance()->images().at(table[k]->anverseName);
		provTex->render(provRect);
	}
}

void IADeckComponent::playCards()
{
	if (enemy->tableCardsLeft() <= 1) //si el player tiene 1 o ninguna cartas la IA jugará su carta de mayor energia puesto que según su lógica será la mejor opción
	{
		selectedHand = hand[0]; selectedHandIt = 0;
		for (int i = 0; i < hand.size(); i++)
		{
			if (hand[i]->energy > selectedHand->energy&&energy-hand[i]->energy>=0) //el costo de enrgia es mayor
			{ 
				selectedHand = hand[i]; selectedHandIt = i; 
			} //siempre habrá una carta que cumpla estas características
			else if (hand[i]->energy == selectedHand->energy && hand[i]->attack > selectedHand->attack)//si cuestan la misma energia se evalua el valor del ataque
			{
				selectedHand = hand[i]; selectedHandIt = i;
			}
		}
		//en esta parte ya no tenemos que evaluar si podemos jugar la carta porque al seleccionar la carta ya hemos comprobado que sea jugable
		table.push_back(selectedHand);
		hand.erase(hand.begin() + selectedHandIt);
		energy -= selectedHand->energy;
		selectedHand = nullptr;

		if (energy > 0 &&hand.size()>0) { playCards(); } //si queda energia después de esta accion y le quedan cartas que jugar se repite la misma lógica
		else { endTurn(); }
	}
	else //este es el caso mas complicado ya que se pueden usar varias estrategias si fuera una persona real pero al ser una IA voy a optar por igualar las cartas que tienen ambos jugadores pero la IA usará las cartas de mayor energia siempre
	{

	}
}