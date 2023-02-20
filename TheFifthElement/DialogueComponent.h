#pragma once
#ifndef DIALOGCOMPONENT_H
#define DIALOGCOMPONENT_H_

 #include "utils/Component.h"
#include "sdlutils/Font.h"
#include "sdlutils/Texture.h"
#include "utils/ecs.h"
class DialogueComponent : public Component
{
private:
	Font* font_;
	//float speed_ = 0.0f;
	GameManager* m;
	int nframes = 0;
	int fila_;
	bool matrix_ = false;
	string stringoriginal;
	string strigsalir;
	SDL_Color color_;
	int cont = 0, fin;
public:
	DialogueComponent(int a ) {
		font_ = &SDLUtils::instance()->fonts().at("TCentury");
		color_ = { 50,50,0 };
		stringoriginal = SDLUtils::instance()->dialog().at(to_string(a));
		strigsalir = stringoriginal[0];
		fin = stringoriginal.size();
	}
	void render() {
		font_->render(m->getRenderer(), strigsalir, 150, 300, color_);

	}
	void update() {
		cont++;
		if (cont < fin)strigsalir += stringoriginal[cont];
	}
	~DialogueComponent() {};

};
#endif