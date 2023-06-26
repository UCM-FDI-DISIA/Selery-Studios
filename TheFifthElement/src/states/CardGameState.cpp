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
	backRect.x = 0; backRect.y = 0; backRect.w = WIN_WIDTH; backRect.h = WIN_HEIGHT;
	// fondo, texto de ronda, ¿texto de turno?, la energia de cada player tiene que encargarse este y mostrarla por lo que necesito: 2 imagenes energía, 2 numeros energía
	//genero las 2 entities
	//player tiene: deckmanager(se encarga de las cartas y el render), inputHandler(clicks en cartas y fin de turno)
	//IA tiene:deckManager(cartas y render)
	//genero el primer turno aleatorio y lo configuro en el vector playersTurn
	turnTimer = sdlutils().currRealTime() + 60000; //un temporizador de 1 minuto
}

void CardGameState::update()
{
	//gestor de tiempo y turnos
	//
}

void CardGameState::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
	//evento de click = boton fin turno o pasarselo a cada carta del player, player getComponent DeckManager handleEvents (no estoy seguro) (seguramente haga un inputHandler que se encargue de esto solo para el player
	//evento de ESC
}

void CardGameState::render()
{
	table->render(backRect);
}