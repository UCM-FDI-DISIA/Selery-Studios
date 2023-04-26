#include "EndState.h"
#include "../Game.h"
EndState::EndState()
{
	//PARA EL TEXTO:
	//carga el tipo de letra
	font_ = &SDLUtils::instance()->fonts().at("TCentury");
	//color de la letra
	color_ = { 255,255,255 };
	creditos = "Tras luchar contra tu propio hermano,$ te das cuenta que el camino no ha sido facil. $ Has intentado ir en contra del viento, nengando lo innegable.$ Sentias tanta ira que te quemaba por dentro,$ intentaste negociar con la muerte,$ casi te ahogas en un mar de lagrimas. $ Pero por fin tras todo eso $ conseguiste superar el duelo.$ Creditos: $ Francisco Miguel Galvan Munoz$ Sheila Julvez Lopez$ Cristina Mora Velasco$ Jose Moreno Barbero$ Dorjee Khampa Herrezuelo Blasco$ Sofia Sánchez Hernandez$ Pablo Cerrada Vega$ Pablo Cao$ Pablo Martinez Quesada$ Agustín Castro$ Alberto Peñalba Martos$";	
	//declaras un stringsteam que te ayude a dividir el texto
	stringstream aux(creditos);
	//cada segmento del texto
	string segment;
	//mientras siga habiendo texto divide el texto original en trozos
	// y los añade en un vector de strings;
	while (std::getline(aux, segment, '$'))
	{
		conespacios.push_back(segment);
	}
	numlineas = conespacios.size();

	Entity* fondo = new Entity();
	Vector2D v = { 0,0 };
	fondo->addComponent<Transform>(TRANSFORM_H, v, 900, 600, 0, 0, 0, false);
	fondo->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("fondoPausa"));
	addEntity(fondo);
	x = 25;
	y = 300;
	// Creacion de los botones
	createButtons();
	//musica 
	//SDLUtils::instance()->soundEffects().at("Menu").play();

}
//destructor
EndState::~EndState()
{
	Manager::~Manager();
}

void EndState::update() {
	Manager::update();
}
void EndState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT ) //boton de salis esquina superior derecha
		{
			GameManager::instance()->getGame()->setExit(true); //cierra sdl
		}
		replay->handleEvent(event); //volver a jugar
		exitButton->handleEvent(event);
		
	}

}
void EndState::render() {
	
	Manager::render();
	double aux = y;
	for (int i = 0; i < numlineas; i++) {
		font_->render(GameManager::instance()->getRenderer(), conespacios[i], x, aux , color_, 45);
		aux += 55;
	}
	y-= 0.2;
}

void EndState::createButtons() {
	//anadimos una entidad que permita volver a jugar 
	replay = new Entity();
	replay->addComponent<Transform>(TRANSFORM_H, Vector2D(2* WIN_WIDTH / 3, 20 * WIN_HEIGHT / 60), 289, 86);
	replay->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("PlayButton"));
	replay->addComponent<Button>(BUTTON_H, "PLAY");
	addEntity(replay);
	//anadimos un boton que permite salir del juego
	exitButton = new Entity();
	exitButton->addComponent<Transform>(TRANSFORM_H, Vector2D(2 * WIN_WIDTH / 3, 35 * WIN_HEIGHT / 60), 289, 86);
	exitButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ExitButton"));
	exitButton->addComponent<Button>(BUTTON_H, "EXIT");
	addEntity(exitButton);


}
