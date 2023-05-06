#include "EndState.h"
#include "../Game.h"
EndState::EndState()
{
	
	//PARA EL TEXTO:
	//carga el tipo de letra
	font_ = &SDLUtils::instance()->fonts().at("TCentury");
	//color de la letra
	color_ = { 255,255,255 };
	creditos = "After fighting against your own brother, $ you realize the path has not been easy. $ You've tried to go against the wind, $ denying the undeniable. $ You felt so much anger that it burned you inside, $ you tried to negotiate with death, $ you almost drowned in a sea of tears. $ But finally, after all that $ you managed to overcome the grief. $ Credits: $ Francisco Miguel Galvan Munoz $ Sheila Julvez Lopez $ Cristina Mora Velasco $ Jose Moreno Barbero $ Dorjee Khampa Herrezuelo Blasco $ Sofia Sanchez Fernandez $ Pablo Cerrada Vega $ Pablo Cao Calvo $ Pablo Martinez Quesada $ Agustin Castro de Troya $ Alberto Penalba Martos $";
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

	Entity* e = new Entity();
	Vector2D pos = { 0,0 };
	e->addComponent<Transform>(TRANSFORM_H, pos, 900, 600, 1);
	Texture* t = &SDLUtils::instance()->images().at("fondoPausa");
	e->addComponent<Image>(IMAGE_H, t);
	addEntity(e);
	x = 25;
	y = 300;
	// Creacion de los botones
	createButtons();
	//musica 
	SDLUtils::instance()->soundEffects().at("Title").play(-1);

	camRect_.x = -5000; 
	camRect_.y = -5000;
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
