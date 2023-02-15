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
	Vector2D DialogBoxVelocity_{ 0,0 };
	float DialogBoxWith_ = 520, DialogBoxHeith_ = 252, DialogBoxRotation_ = 0;
	Texture* t;
	Transform* tr;
	GameManager* m;
	int nframes = 1;
	int w = 58;
	int h = 27;
public:
	DialogBox(GameManager* gm_) {
		font_ = new Font("./assets/fonts/text.ttf", 35);
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, DialogBoxPosition_, DialogBoxVelocity_, DialogBoxWith_, DialogBoxHeith_, DialogBoxRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/fonts/image.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		addComponent<Image>(int(IMAGE_H), t, nframes);

	}
	virtual ~DialogBox() {

	}

protected:


};
#endif // !DIALOGBOX_H



