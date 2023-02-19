#pragma once
#ifndef DIALOGBOX_H_
#define DIALOGBOX_H_
#include "sdlutils/Font.h"
#include "utils/Entity.h"
#include "sdlutils/Texture.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "GameManager.h"
#include "Image.h"
class DialogBox: public Entity {
private:
	Font* font_;
	//Component* componenete;
	Vector2D DialogBoxPosition_{ 20,190 };
	//float speed_ = 0.0f;
	float DialogBoxWith_ = 520, DialogBoxHeith_ = 252, DialogBoxRotation_ = 0;
	Texture* t;
	GameManager* m;
	int nframes = 0;
	int w = 58;
	int h = 27;
	int fila_;
	bool matrix_ = false;
	string stringoriginal;
	string strigsalir;
	SDL_Color color_ ;
	int cont=0, fin;
public:
	DialogBox(GameManager* gm_, int a) {
		m = gm_;
		color_ = { 50,50,0 };
		font_ = &SDLUtils::instance()->fonts().at("TCentury");
		stringoriginal = SDLUtils::instance()->dialog().at(to_string(a));
		cmpId_type z = int(TRANSFORM_H);
		addComponent<Transform>(z, DialogBoxPosition_, DialogBoxWith_, DialogBoxHeith_, DialogBoxRotation_, nframes, matrix_);
		t = new Texture(gm_->getRenderer(), "./assets/fonts/image.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);
		strigsalir = stringoriginal[0];
		fin = stringoriginal.size();
	}
	void render() {
		Entity::render();
		font_->render(m->getRenderer(), strigsalir, 150,300, color_);
	}
	void update() {
		Entity::update();
		cont++;
		if (cont<fin)strigsalir += stringoriginal[cont];
	}
	virtual ~DialogBox() {
		
	}
	
protected:


};
#endif // !DIALOGBOX_H



