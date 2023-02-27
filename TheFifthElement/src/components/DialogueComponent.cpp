#include "DialogueComponent.h"
#include "../Entities/DialogBox.h"
DialogueComponent::DialogueComponent(int a) :Component() {
	//coge el tipo de letra
	font_ = &SDLUtils::instance()->fonts().at("TCentury");
	//de que color va a salir, en este caso negro
	color_ = { 50,50,0 };
	//coge el dialogo completo 
	stringoriginal = SDLUtils::instance()->dialog().at(to_string(a));
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
	//coges la primera letra del dialogo
	out = conespacios[0][0];
	fin = conespacios[0].size();
	
}
void DialogueComponent::render() {
	//renderizas el texto
	font_->render(GameManager::instance()->getRenderer(), out, 150, 300, color_);

}
void DialogueComponent::update() {
	//en el update hay que mostrar el nuevo contenido.
	cont++;
	if (cont < fin)out += conespacios[static_cast<DialogBox*>(ent_)->getline()][cont];
	

}
void DialogueComponent::changeline() {
	int aux = static_cast<DialogBox*>(ent_)->getline();
	if (aux >= conespacios.size()-1) {
		static_cast<DialogBox*>(ent_)->setfinish(true);
	}
	else {
		fin = conespacios[aux].size();
		cont = 0;
		out = "";
	}
	
}
//virtual DialogueComponent::~DialogueComponent() {}

