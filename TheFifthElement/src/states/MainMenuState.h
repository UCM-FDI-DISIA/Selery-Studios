#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
#include "../components/sliderComponent.h"
#include "../components/FramedImage.h"


class MainMenuState : public Manager
{
private:
	Entity* playButton;
	Entity* exitButton;
	Entity* optionsButton;
	Entity* slider;
	Entity* loadButton;
	bool controladorDetectado;
	SDL_GameController* controller;
	
public:
	MainMenuState();
	~MainMenuState();
	virtual string getStateID() { return "MainMenu"; }; // stringID
	void update();
	void handleEvents();
	void render();

	Entity* addNewEntity(string t, float w, float h, Vector2D pos, int nframes, int wFrame, int hFrame, bool flip, float size = 1);

	void Background(string file);



	void createButtons();
};

