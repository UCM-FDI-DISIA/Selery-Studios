#include "DialogueComponent.h"
#include "../utils/Entity.h"
#include "../utils/Constants.h"
#include "../states/TopDownState.h"
DialogueComponent::DialogueComponent():Component() {
	//coge el tipo de letra
	font_ = &SDLUtils::instance()->fonts().at("TCentury");
	//de que color va a salir, en este caso negro
	color_ = { 50,50,0 };
	hasstarted = false;
	openedShop_ = false;
}
void DialogueComponent::initComponent() {
	plynpc = ent_->getComponent<PlayerNPC>(PLAYERNPC_H);
	t = &SDLUtils::instance()->images().at("papiro");
}
void DialogueComponent::setdialogue() {
	//coge el dialogo completo 
	stringoriginal = SDLUtils::instance()->dialog().at(to_string(plynpc->getcol()));
	//declaras un stringsteam que te ayude a dividir el texto
	stringstream aux(stringoriginal);
	//cada segmento del texto
	string segment;
	//mientras siga habiendo texto divide el texto original en trozos
	// y los añade en un vector de strings;
	while (std::getline(aux, segment, '$'))
	{
		conespacios.push_back(segment);
	}
	//seteas el contador a 0
	cont = 0;
	linea = 0;
	//coges la primera letra del dialogo
	out = conespacios[0][0];
	fin = conespacios[0].size();
}
void DialogueComponent::render() {
	//renderizas el texto
	if (hasstarted) {
		Vector2D a;
		if (WIN_WIDTH / 900 == 1920 / 900) a = Vector2D(600, 600);
		else a = Vector2D(100, 250);
		SDL_Rect dest = build_sdlrect(a, DIALOGUE_WIDTH, DIALOGUE_HEIGHT);
		t->render(dest, 0);

		if (WIN_WIDTH / 900 == 1920 / 900) a = Vector2D(740, 750);
		else a = Vector2D(230, 400);
		font_->render(GameManager::instance()->getRenderer(), out, a.getX(), a.getY(), color_);
	
	}

}
void DialogueComponent::update() {
	//en el update hay que mostrar el nuevo contenido.
	/*cont++;
	if (cont < fin)out += conespacios[static_cast<DialogBox*>(ent_)->getline()][cont];*/
	if (hasstarted) {
		cont++;
		if (cont < fin)out += conespacios[linea][cont]; 
	}
}
void DialogueComponent::inicombe() {
	if (plynpc->getcol() != -1) {
		if (hasstarted == false) {
			setdialogue();
			hasstarted = true;
		}
		else {
			if (linea < conespacios.size()-1) {
				linea++;
				out = "";
				cont = 0;
				fin = conespacios[linea].size();
			}
			else {
				if (quest && !quest1) { static_cast<TopDownState*>(mngr_)->newQuest("hermanos", "Reune a tus hermanos", "monedas", 300, 3); quest1 = true; }
				else if (quest) { static_cast<TopDownState*>(mngr_)->newQuest("enemigos", "Elimina a 5 enemigos", "Desbloqueo de zona", 0, 5); quest = false; }
				hasstarted = false;
				conespacios.clear();
				if (plynpc->getcol() == 22) {
					static_cast<TopDownState*>(mngr_)->DeleteContexto();
				}
				if (plynpc->getcol() <=4) {
					openedShop_ = true;
					static_cast<TopDownState*>(mngr_)->createShopButtons();
				} 
			}
		}
	}
	
}
void DialogueComponent::changeline() {
	/*int aux = static_cast<DialogBox*>(ent_)->getline();
	if (aux >= conespacios.size()-1) {
		static_cast<DialogBox*>(ent_)->setfinish(true);
	}
	else {
		fin = conespacios[aux].size();
		cont = 0;
		out = "";
	}*/
	
}
//virtual DialogueComponent::~DialogueComponent() {}



