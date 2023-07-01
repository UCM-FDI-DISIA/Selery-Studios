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
	//genero todo el plano, la font, y algun elemento extra necesario:
	table= &SDLUtils::instance()->images().at("cardTable");
	font = &SDLUtils::instance()->fonts().at("TCenturyScale");
	energyTex= &SDLUtils::instance()->images().at("energy");
	
	//generamos todas las cartas manualmente: 16 commonCards, 4 unicas para el player y 3 unicas para la IA
	commonCards = {{"WaterSkeleton",1,2,2,1,generalreverse}, {"WaterGoblin",1,1,3,1,generalreverse} , {"WaterMushroom",2,3,1,1,generalreverse} , {"WaterBat",1,1,1,1,generalreverse}, 
	 {"FireSkeleton",1,2,2,2,generalreverse} , {"FireGoblin",1,1,3,2,generalreverse} , {"FireMushroom",2,3,1,2,generalreverse} , {"FireBat",1,1,1,2,generalreverse} ,
	 {"EarthSkeleton",1,2,2,3,generalreverse} , {"EarthGoblin",1,1,3,3,generalreverse} , {"EarthMushroom",2,3,1,3,generalreverse} , {"EarthBat",1,1,1,3,generalreverse} ,
	 {"WindSkeleton",1,2,2,4,generalreverse} , {"WindGoblin",1,1,3,4,generalreverse} , {"WindMushroom",2,3,1,4,generalreverse} , {"WindBat",1,1,1,4,generalreverse} };
	IACards = {  {"WaterBoss",5,5,5,1,generalreverse} , {"FireBoss",5,5,5,2,generalreverse} , {"EarthBoss",5,5,5,3,generalreverse} };
	playerCards = {  {"WaterSister",4,4,4,1,generalreverse} , {"FireBrother",4,4,4,2,generalreverse} , {"EarthBrother",4,4,4,3,generalreverse} , {"WindBrother",4,4,4,4,generalreverse} };

	//player tiene: deckmanager(se encarga de todo)
	player = new Entity();
	player->setContext(this);
	playerDeck=player->addComponent<DeckManagerComponent>(DECKMANAGERCOMPONENT_H,Gm_, player);
	player->addComponent<Transform>(TRANSFORM_H, Vector2D(110, WIN_HEIGHT/2+70), 80, 80); //hay que cambiarlo por el release
	player->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("perfilPlayer"));
	playerLife = player->addComponent<CardPlayerLifeComponent>(CARDPLAYERLIFECOMPONENT_H, 20);
	addEntity(player);

	//IA tiene:deckManager distinto(cartas y render)
	IA = new Entity();
	IA->setContext(this);
	IADeck = IA->addComponent<IADeckComponent>(IADECKCOMPONENT_H,Gm_, IA, playerDeck); //le pasamos el player para que la IA ejecute acciones en base a lo que ve
	IA->addComponent<Transform>(TRANSFORM_H, Vector2D(110, 300), 80, 80); //hay que cambiarlo por el release
	IA->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("perfilIA"));
	IALife = IA->addComponent<CardPlayerLifeComponent>(CARDPLAYERLIFECOMPONENT_H, 20);
	addEntity(IA);

	turnTimer = sdlutils().currRealTime() + 60000; //un temporizador de 1 minuto
	numTurno = 1; numRonda = 1; playerDeck->receiveEnergy(numRonda); IADeck->receiveEnergy(numRonda);

	//llamamos al deal para darles cartas a los jugadores y despues hacemos un draw card de 5 para cada uno
	deal();
	playerDeck->drawCard(5);
	IADeck->drawCard(5);
	//sonidos de la partida
	SDLUtils::instance()->soundEffects().at("cardShuffle").play();
	SDLUtils::instance()->musics().at("cardMusic").play();
	Mix_Music* music = Mix_LoadMUS("cardMusic");
	Mix_PlayMusic(music, -1);
}

void CardGameState::update()
{
	if(!end)
	{
		handleEvents();
		//gestor de tiempo y turnos
		if (numTurno == 1) //turno del player tiene contador y se llama a handleevents del player
		{
			if (turnTimer <= sdlutils().currRealTime()&&!paused) //si se acaba el tiempo
			{
				nextTurn();
			}
		}
		else //siempre será numTurno==2, turno de la IA
		{
			IADeck->playCards();
		}
	}
	else
	{
		if (timerEnd <= sdlutils().currRealTime())
		{
			GameManager::instance()->backToMainMenu();
		}
	}
}

void CardGameState::handleEvents()
{
	if(!end)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type==SDL_KEYDOWN&&event.key.keysym.sym==SDLK_ESCAPE)
			{
				Mix_HaltMusic();
				pausedGame(true);
				GameManager::instance()->goCardsPause(this);
			}

			if (numTurno == 1)
			{
				playerDeck->handleEvents(event);
			}
		}
	}
}

void CardGameState::render()
{
	table->render(backRect);
	player->render();
	IA->render();
	energyTex->render({ 1680,250,100,100 }); //energia de la IA
	font->render(Gm_->getRenderer(), to_string(IADeck->getEnergy()), 1725, 290, colorFont);
	energyTex->render({ 1680,510,100,100 }); //energia del player
	font->render(Gm_->getRenderer(), to_string(playerDeck->getEnergy()), 1725, 550, colorFont);
	font->render(Gm_->getRenderer(), " Ronda", 136, 470, colorFont);
	font->render(Gm_->getRenderer(), to_string(numRonda), 178, 450, colorFont);
	font->render(Gm_->getRenderer(), to_string((turnTimer-sdlutils().currRealTime())/1000), 102, 450, colorFont);
	//vida del player
	font->render(Gm_->getRenderer(), to_string(playerLife->lifeLeft()), 120, WIN_HEIGHT / 2 + 180, { 255,255,255 });
	//vida de la IA
	font->render(Gm_->getRenderer(), to_string(IALife->lifeLeft()), 120, 410, { 255,255,255 });
	if (numTurno == 1) { playerTurn->render(sliderRect); }
	else { IATurn->render(sliderRect); }
	if (end) { endGameTex->render(enGameRect); }
}

void CardGameState::nextTurn()
{
	if (numTurno == 1) //si era el turno del player
	{
		numTurno++;
		IADeck->drawCard(1);
		SDLUtils::instance()->soundEffects().at("cardDeal").play();
		IADeck->receiveEnergy(numRonda);
		IADeck->addTableTurn();
	}
	else //si es el segundo turno
	{
		numRonda++;
		numTurno--;
		turnTimer = sdlutils().currRealTime() + 60000; //se reestablece el contador para el player
		playerDeck->receiveEnergy(numRonda);
		playerDeck->drawCard(1);
		SDLUtils::instance()->soundEffects().at("cardDeal").play();
		playerDeck->addTableTurn();
	}
}

void CardGameState::deal()
{
	for (int i = 0; i < 20; i++)
	{
		int chooseStack = rand() % 5 + 1;
		if (chooseStack == 1&&playerCards.size()!=0)
		{
			int chooseCard = rand() % (playerCards.size());//aqui no hago un +1 ya que existe el indice 0 pero no el indice playerCards.size() por estar fuera de rango
			playerDeck->shuffleDeck(new CardsInfo{ playerCards[chooseCard].anverseName, playerCards[chooseCard].energy, playerCards[chooseCard].life, playerCards[chooseCard].attack, playerCards[chooseCard].element, playerCards[chooseCard].reverse });
			playerCards.erase(playerCards.begin()+chooseCard); //se elimina la carta de la pila para que el player no tenga más de 1 de cada y no se dé el caso de que tenga 4 veces al hermano de fuego (balance del juego)
		}
		else
		{
			int chooseCard = rand() % (commonCards.size());
			playerDeck->shuffleDeck(new CardsInfo{ commonCards[chooseCard].anverseName, commonCards[chooseCard].energy, commonCards[chooseCard].life, commonCards[chooseCard].attack, commonCards[chooseCard].element, commonCards[chooseCard].reverse }); //no se hace erase ya que se pueden tener cartas repetidas de esta pila y porque luego la IA las necesita también
		}
	}
	//parte de la IA //descomentar cuando esté terminado el componente
	for (int j = 0; j < 20; j++)
	{
		int chooseStack = rand() % 5 + 1;
		if (chooseStack == 1 && IACards.size() != 0)
		{
			int chooseCard = rand() % (IACards.size());//aqui no hago un +1 ya que existe el indice 0 pero no el indice playerCards.size() por estar fuera de rango
			IADeck->shuffleDeck(new CardsInfo{ IACards[chooseCard].anverseName, IACards[chooseCard].energy, IACards[chooseCard].life, IACards[chooseCard].attack, IACards[chooseCard].element, IACards[chooseCard].reverse });
			IACards.erase(IACards.begin() + chooseCard); //se elimina la carta de la pila para que el player no tenga más de 1 de cada y no se dé el caso de que tenga 4 veces al hermano de fuego (balance del juego)
		}
		else
		{
			int chooseCard = rand() % (commonCards.size());
			IADeck->shuffleDeck(new CardsInfo{ commonCards[chooseCard].anverseName, commonCards[chooseCard].energy, commonCards[chooseCard].life, commonCards[chooseCard].attack, commonCards[chooseCard].element, commonCards[chooseCard].reverse }); //no se hace erase ya que se pueden tener cartas repetidas de esta pila y porque luego la IA las necesita también
		}
	}
}

void CardGameState::clashCards(CardsInfo* cardPlayer, CardsInfo* cardIA)
{
	if (cardPlayer->element == cardIA->element) //mismo elemento
	{
		cardPlayer->life -= cardIA->attack;
		cardIA->life -= cardPlayer->attack;
	}
	else if (cardPlayer->element == 1 && cardIA->element == 2)//agua vs fuego
	{
		cardPlayer->life -= cardIA->attack-1;
		cardIA->life -= cardPlayer->attack+1;
	}
	else if (cardPlayer->element == 2 && cardIA->element == 3)//fuego vs tierra
	{
		cardPlayer->life -= cardIA->attack-1;
		cardIA->life -= cardPlayer->attack+1;
	}
	else if (cardPlayer->element == 3 && cardIA->element == 1)//tierra vs agua
	{
		cardPlayer->life -= cardIA->attack-1;
		cardIA->life -= cardPlayer->attack+1;
	}
	else if (cardPlayer->element == 1 && cardIA->element == 3)//agua vs tierra
	{
		cardPlayer->life -= cardIA->attack+1;
		cardIA->life -= cardPlayer->attack-1;
	}
	else if (cardPlayer->element == 2 && cardIA->element == 1)//fuego vs agua
	{
		cardPlayer->life -= cardIA->attack+1;
		cardIA->life -= cardPlayer->attack-1;
	}
	else if (cardPlayer->element == 3 && cardIA->element == 2)//tierra vs fuego
	{
		cardPlayer->life -= cardIA->attack+1;
		cardIA->life -= cardPlayer->attack-1;
	}
	else if (cardPlayer->element == 4 || cardIA->element == 4)//elemento de aire es neutro para todos
	{
		cardPlayer->life -= cardIA->attack;
		cardIA->life -= cardPlayer->attack;
	}
	playerDeck->reviewCards();
	IADeck->reviewCards();
}

void CardGameState::attackPlayer(CardsInfo* card)
{
	playerLife->damage(card->attack);
	//if el player se muere
}

void CardGameState::attackIA(CardsInfo* card)
{
	IALife->damage(card->attack);
	//if la IA se muere
}

bool CardGameState::canAttackIA()
{
	if (IADeck->tableCardsLeft() == 0) return true;
	else return false;
}

void CardGameState::endMatch(Entity* winner)
{
	end = true;
	timerEnd = sdlutils().currRealTime()+5000;
	if (winner==player) { endGameTex = &SDLUtils::instance()->images().at("victory"); } //puede que falle
	else { endGameTex = &SDLUtils::instance()->images().at("defeat"); }
}

void CardGameState::pausedGame(bool setPause)
{
	paused = setPause;
	if (paused)
	{
		pausedTime = sdlutils().currRealTime();
	}
	else
	{
		int elapsedTime = sdlutils().currRealTime() - pausedTime;
		turnTimer += elapsedTime;
	}
}