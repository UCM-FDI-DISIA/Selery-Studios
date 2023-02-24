#pragma once
#ifndef DIALOGBOX_H_
#define DIALOGBOX_H_

#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../GameManager.h"
#include "../components/Image.h"
#include "../components/DialogueComponent.h"
class DialogBox: public Entity {
private:
	Vector2D DialogBoxPosition_{ 20,190 };
	float DialogBoxWith_ = 520, DialogBoxHeith_ = 252, DialogBoxRotation_ = 0;
	Texture* t;
	int nframes = 0;
	int fila_;
	bool matrix_ = false;
public:
	DialogBox(int a) {
		cmpId_type z = int(TRANSFORM_H);
		addComponent<Transform>(z, DialogBoxPosition_, DialogBoxWith_, DialogBoxHeith_, DialogBoxRotation_, nframes, matrix_);
		t = new Texture(GameManager::instance()->getRenderer(), "./assets/fonts/image.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);
		addComponent<DialogueComponent>(int(DIALOGCOMPONENT_H), a);
	}
	virtual ~DialogBox() {
		
	}
	
protected:


};
#endif // !DIALOGBOX_H



