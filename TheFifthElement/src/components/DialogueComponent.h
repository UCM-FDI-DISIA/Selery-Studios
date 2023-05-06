#pragma once
#ifndef DIALOGCOMPONENT_H
#define DIALOGCOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/Font.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include <sstream>
#include <string>
#include <vector>;
#include "Playernpc.h"
#include "../GameManager.h"
#include "../Quests.h"
using namespace std;
class DialogueComponent : public Component
{
private:
	Font* font_;
	PlayerNPC* plynpc;
	string stringoriginal;
	vector<string> conespacios;
	vector<bool> tutorial{false,false,false, false, false};
	string out;
	SDL_Color color_;
	bool hasstarted;
	bool openedShop_;
	int cont = 0, fin, linea =0;
	int d;
	Texture* t;
public:
	DialogueComponent();
	void render();
	void update();
	void initComponent();
	void setdialogue();
	void inicombe();
	virtual ~DialogueComponent() { };
	bool gethasstarted() { return hasstarted; }
	bool getopenedShop() { return openedShop_; }
	void setopenedShop() { openedShop_ = false; }

};
#endif