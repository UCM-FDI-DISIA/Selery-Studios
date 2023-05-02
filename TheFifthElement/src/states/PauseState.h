#pragma once
#include "../utils/Manager.h"
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"


class PauseState : public Manager
{
private:
	Entity* resumeButton;
	Entity* menuButton;
	Entity* optionsButton;
	Image* im_;
	bool controladorDetectado;
	SDL_GameController* controller;
	
public:
	PauseState();
	~PauseState() {};
	virtual string getStateID() { return "Pause"; }; // stringID
	void update();
	void handleEvents();
	void render();

	Entity* addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size = 1, bool neg = false);
	Entity* createCharacter(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size);
	void Background(string file);
	void createButtons();

};

