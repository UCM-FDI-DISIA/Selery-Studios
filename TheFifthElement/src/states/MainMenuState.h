#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
#include "../components/sliderComponent.h"
class MainMenuState : public Manager
{
private:
	Entity* playButton;
	Entity* exitButton;
	Entity* optionsButton;
	Entity* slider;
	Image* im_;
public:
	MainMenuState();
	~MainMenuState() {};
	virtual string getStateID() { return "MainMenu"; }; // stringID
	void update();
	void handleEvents();
	void render();

	Entity* addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size = 1);

	void Background(string file);

	void createButtons();
};

