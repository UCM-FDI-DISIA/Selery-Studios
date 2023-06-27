#include "CardGameState.h"

//necesito generar una pila de 20 cartas de manera aleatoria
//voy a crear 3 listas posbiles: comunes, player, maquina
//comunes tendrán todos los enemigos con sus correspondientes elementos
//player tendrá los 4 personajes y un ataque de cada tipo
//maquina tendrá los 3 bosses 

//primero se generan las 2 barajas y luego se dan las 5 primeras a cada uno y pasan del vector baraja al vector mano
//cuando se seleccione una cara de la mano se colocará un poco más grande (todavía no sé
//debo tener un deck manager component que se añada a la entity player y a la entity IA que se encargue de las 2 listas
//al inicio se darán las 20 cartas al deckmanagercomoponent que las almacenará en su vector deck mediante pushback
//tras repartir las cartas se llamrá a una funcion que añade 1 carta del deck a la mano (se hace de 1 en una para reutilizar ese metodo a la hora de de añadir cartas en el nuevo turno)
//¿Debería añadir una entity matchManager que maneje los turnos o lo hace el porpio CardsGameState? Que se encargue este script
//los turnos son 2 y el primero es aleatorio por lo que al iniciar se añadirán las enities a un contenedor que irás yendo uno por uno ejecutando los turnos

CardGameState::CardGameState()
{
	//genero todo el plano:
	table= &SDLUtils::instance()->images().at("cardTable");
	font = &SDLUtils::instance()->fonts().at("TCenturyScale");
	energyTex= &SDLUtils::instance()->images().at("energy");
	//texto de ronda, la energia de cada player tiene que encargarse este y mostrarla por lo que necesito: 2 imagenes energía, 2 numeros energía

	//player tiene: deckmanager(se encarga de todo)
	player = new Entity();
	player->setContext(this);
	playerDeck=player->addComponent<DeckManagerComponent>(DECKMANAGERCOMPONENT_H, player);
	player->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2 - 80, WIN_HEIGHT - 160), 80, 80);
	player->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("perfilPlayer"));
	addEntity(player);

	//IA tiene:deckManager distinto(cartas y render)
	IA = new Entity();
	IA->setContext(this);
	IADeck = IA->addComponent<IADeckComponent>(IADECKCOMPONENT_H, IA, player); //le pasamos el player para que la IA ejecute acciones en base a lo que ve
	IA->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2 - 80, 0), 80, 80);
	IA->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("perfilIA"));
	addEntity(IA);

	turnTimer = sdlutils().currRealTime() + 2000; //un temporizador de 1 minuto
	numTurno = 1; numRonda = 1; playerDeck->receiveEnergy(numRonda);
	//llamamos a un metodo para asignar las cartas de las pools de cartas
}

void CardGameState::update()
{
	//gestor de tiempo y turnos
	if (numTurno == 1) //turno del player tiene contador y se llama a handleevents del player
	{
		if (turnTimer <= sdlutils().currRealTime()) //si se acaba el tiempo
		{
			nextTurn();
		}
		else
		{
			playerDeck->handleEvents();
		}
	}
	else //siempre será numTurno==2, turno de la IA
	{
		nextTurn(); //todavía no está la IA por lo que me salto el turno
	}
}

void CardGameState::handleEvents()
{
    SDL_Event event;
	while (SDL_PollEvent(&event))
	{

	}
	//evento de ESC
}

void CardGameState::render()
{
	table->render(backRect);
	player->render();
	IA->render();
	energyTex->render({ 1680,250,100,100 }); //energia de la IA
	font->render(Gm_->getRenderer(), to_string(playerDeck->getEnergy()), 1725, 290, colorFont);
	energyTex->render({ 1680,510,100,100 }); //energia del player
	font->render(Gm_->getRenderer(), to_string(playerDeck->getEnergy()), 1725, 550, colorFont);
	font->render(Gm_->getRenderer(), " Ronda", 136, 470, colorFont);
	font->render(Gm_->getRenderer(), to_string(numRonda), 178, 450, colorFont);
	font->render(Gm_->getRenderer(), to_string((turnTimer-sdlutils().currRealTime())/1000), 100, 450, colorFont);
	//render de la insignia de turno con un if para detectar a quien colocarsela
	//deberia hacer aquí el render de la cantidad de cartas de cada uno
}

void CardGameState::nextTurn()
{
	if (numTurno == 1) //si era el turno del player
	{
		numTurno++;
	}
	else //si es el segundo turno
	{
		numRonda++;
		numTurno--;
		turnTimer = sdlutils().currRealTime() + 2000; //se reestablece el contador para el player
		playerDeck->receiveEnergy(numRonda);
	}
}

void CardGameState::deal()
{
	//hago un for hasta 20 para cada entity
}