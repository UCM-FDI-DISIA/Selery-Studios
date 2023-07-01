#pragma once
#include "../utils/Manager.h"
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"

class CardGameState;

class CardPauseState :public Manager
{
private:
	Entity* menuButton;
	Entity* returnButton;
	Entity* idk;
	Texture* controlsTex = &SDLUtils::instance()->images().at("cardControls"); //cambiar el nombre
	CardGameState* cardState; //puntero al estado para luego reestablecer el temporizador de turnos
public:
	CardPauseState(CardGameState* cardState_);
	~CardPauseState() {}

	virtual string getStateID() { return "CardPause"; }; // stringID
	virtual void update() { Manager::update(); }
	virtual void handleEvents();
	virtual void render();
	virtual void createButtons();
	CardGameState* getCardState() { return cardState; }
};