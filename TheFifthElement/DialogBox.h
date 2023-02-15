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
	Transform* tr;
	GameManager* m;
	int nframes = 0;
	int w = 58;
	int h = 27;
	int fila_;
public:
	DialogBox(GameManager* gm_) {
		font_ = new Font("./assets/fonts/text.ttf", 35);
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, DialogBoxPosition_, DialogBoxWith_, DialogBoxHeith_, DialogBoxRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/fonts/image.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);

	}
	virtual ~DialogBox() {

	}

protected:


};
#endif // !DIALOGBOX_H



