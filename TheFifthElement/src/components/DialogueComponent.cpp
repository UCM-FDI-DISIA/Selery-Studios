#include "DialogueComponent.h"
#include "../utils/Entity.h"
#include "../utils/Constants.h"
#include "../states/TopDownState.h"
DialogueComponent::DialogueComponent():Component() {
	//coge el tipo de letra
	if (WIN_WIDTH == 1920)font_ = &SDLUtils::instance()->fonts().at("TCenturyScale");
	else font_ = &SDLUtils::instance()->fonts().at("TCentury");
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
		SDL_Rect dest;
		if (WIN_WIDTH == 1920) 
		{
			a = Vector2D(550, 500); 
			dest = build_sdlrect(a,920, 533);
		}
		else 
		{ 
			a = Vector2D(100, 250); 
			dest = build_sdlrect(a, DIALOGUE_WIDTH, DIALOGUE_HEIGHT);
		}

		//SDL_Rect dest = build_sdlrect(a, DIALOGUE_WIDTH * (WIN_WIDTH/900), DIALOGUE_HEIGHT * (WIN_HEIGHT / 600));
		t->render(dest, 0);

		if (WIN_WIDTH == 1920) a = Vector2D(750, 750);
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
			if (linea < conespacios.size() - 1) {
				linea++;
				out = "";
				cont = 0;
				fin = conespacios[linea].size();
			}
			else {

				hasstarted = false;
				conespacios.clear();
				int numeronpc = plynpc->getcol();
				if (numeronpc == 5) {
					static_cast<TopDownState*>(mngr_)->DeleteContexto();
					static_cast<TopDownState*>(mngr_)->newQuest("siblings", "Gather your siblings", "coins", 300, 3);
					static_cast<TopDownState*>(mngr_)->newQuest("villagers", "Talk to villagers", "Area unlock", 0, 1);
				}
				else if (numeronpc > 5 && numeronpc <= 11 && !tutorial[numeronpc - 6]) {
					Quests::instance()->completedQuest("villagers");
					tutorial[numeronpc - 6] = true;			
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



