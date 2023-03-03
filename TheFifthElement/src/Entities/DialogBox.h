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
	float DialogBoxWith_ = DIALOGUE_WIDTH / 2, DialogBoxHeith_ = DIALOGUE_HEIGHT / 2, DialogBoxRotation_ = 0, speed=0;
	Texture* t;
	DialogueComponent* d;
	int nframes = 0;
	int fila_;
	bool matrix_ = false;
	bool finish_ = false;
	int line_=0;
public:
	
	DialogBox(int a) {
		addComponent<Transform>(TRANSFORM_H, DialogBoxPosition_, DialogBoxWith_, DialogBoxHeith_, DialogBoxRotation_,speed, nframes, matrix_);
		t = new Texture(GameManager::instance()->getRenderer(), "./assets/Texts/image.png");
		fila_ = 0;
		addComponent<Image>(IMAGE_H, t, nframes, nframes, fila_, DIALOGUE_WIDTH, DIALOGUE_HEIGHT);
		d = addComponent<DialogueComponent>(DIALOGCOMPONENT_H, a);
	}
	virtual ~DialogBox() {
	}
	bool getfinish() {
		return finish_;
	}
	void setfinish(bool fin) {
		finish_ = fin;
	}
	int getline() {
		return line_;
	}
	void setline() {
		line_ ++;
		cout << line_;
		d->changeline();
	}
protected:


};
#endif // !DIALOGBOX_H



