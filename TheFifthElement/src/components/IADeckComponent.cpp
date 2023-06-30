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
	if (hand.size() > 0&&energy>0)
	{
		if (enemy->tableCardsLeft() <= 1) //si el player tiene 1 o ninguna cartas la IA jugará su carta de mayor energia puesto que según su lógica será la mejor opción
		{
			selectedHandEnergy = 0;
			for (int i = 0; i < hand.size(); i++)
			{
				if (hand[i]->energy > selectedHandEnergy && energy - hand[i]->energy >= 0) //el costo de energia es mayor
				{
					selectedHand = hand[i]; selectedHandIt = i; selectedHandEnergy = hand[i]->energy;
				} //siempre habrá una carta que cumpla estas características
				else if (hand[i]->energy == selectedHandEnergy && hand[i]->attack > selectedHand->attack)//si cuestan la misma energia se evalua el valor del ataque
				{
					selectedHand = hand[i]; selectedHandIt = i;
				}
			}
			//en esta parte ya no tenemos que evaluar si podemos jugar la carta porque al seleccionar la carta ya hemos comprobado que sea jugable
			table.push_back(selectedHand);
			hand.erase(hand.begin() + selectedHandIt);
			energy -= selectedHandEnergy;
			selectedHand = nullptr;
			selectedHandEnergy = 0;

			if (energy > 0 && hand.size() > 0) { playCards(); } //si queda energia después de esta accion y le quedan cartas que jugar se repite la misma lógica
			else { playAttack(); }
		}
		else //este es el caso mas complicado ya que se pueden usar varias estrategias si fuera una persona real pero al ser una IA voy a optar por llenar la mesa de cartas para dificultar el proximo ataque al jugador
		{
			selectedHandEnergy = 10;//es un caso que nunca se va a dar pero lo vamos a usar para luego elegir la carta con menor valor energetico
			for (int i = 0; i < hand.size(); i++)
			{
				if (hand[i]->energy < selectedHandEnergy && energy - hand[i]->energy >= 0) { selectedHand = hand[i]; selectedHandIt = i; selectedHandEnergy = hand[i]->energy; }
				else if (hand[i]->energy == selectedHandEnergy && energy - hand[i]->energy >= 0 && hand[i]->attack > selectedHand->energy) //aqui no se da fallo ya que nunca entrará si todavia no se ha escogido carta ya que selectedHandEnergy será 10
				{
					selectedHand = hand[i];
					selectedHandIt = i;
				}
			}
			//una vez hemos encontrado la carta de menor coste de energia la jugamos
			table.push_back(selectedHand);
			hand.erase(hand.begin() + selectedHandIt);
			energy -= selectedHand->energy;
			selectedHand = nullptr;
			if (energy > 0 && hand.size() > 0) { playCards(); } //si queda energia después de esta accion y le quedan cartas que jugar se repite la misma lógica
			else { playAttack(); }
		}
	}
	else { playAttack(); }
}

void IADeckComponent::addTableTurn()
{
	for (int i = 0; i < table.size(); i++)
	{
		table[i]->numTableTurns++;
		table[i]->attacked = false;
	}
}

void IADeckComponent::playAttack()
{
	for (int i = 0; i < table.size(); i++)
	{
		if (!table[i]->attacked && table[i]->numTableTurns > 0) //la carta puede atacar
		{
			if (enemy->tableCardsLeft()==0)
			{
				static_cast<CardGameState*>(mngr_)->attackPlayer(table[i]);
			}
			else
			{
				static_cast<CardGameState*>(mngr_)->clashCards(enemy->firstTableCard(), table[i]);
				table[i]->attacked = true;
			}
		}
	}
	endTurn();
}

void IADeckComponent::reviewCards()
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i]->life <= 0) { table.erase(table.begin() + i); }
	}
}