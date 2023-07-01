#pragma once
#include "../utils/Manager.h"
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"

class CardPauseState :public Manager
{
private:
	Entity* menuButton;
	Entity* returnButton;
	Texture* controlsTex = &SDLUtils::instance()->images().at("cardControls"); //cambiar el nombre
public:
	CardPauseState() { createButtons(); };
	~CardPauseState() {}

	virtual string getStateID() { return "CardPause"; }; // stringID
	virtual void update() {}
	virtual void handleEvents();
	virtual void render();
	virtual void createButtons();
};