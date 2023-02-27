#pragma once
#ifndef DIALOGCOMPONENT_H
#define DIALOGCOMPONENT_H_

#include "../utils/Component.h"
#include "../sdlutils/Font.h"
#include "../sdlutils/Texture.h"
#include "../utils/ecs.h"
#include <sstream>
#include <string>
#include <vector>;
using namespace std;
class DialogueComponent : public Component
{
private:
	Font* font_;
	//float speed_ = 0.0f;
	//int nframes = 0;
	//int fila_;
	//bool matrix_ = false;
	
	string stringoriginal;
	vector<string> conespacios;
	string out;
	SDL_Color color_;
	int cont = 0, fin;
	int d;
public:
	DialogueComponent(int a);
	void render();
	void update();
	void changeline();
	//virtual ~DialogueComponent();

};
#endif