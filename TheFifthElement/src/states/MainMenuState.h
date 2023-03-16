#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
#include "../../sliderComponent.h"
class MainMenuState : public Manager
{
private:
	Entity* playButton;
	Entity* exitButton;
	Entity* optionsButton;
	Entity* slider;
	Image* im_;

	float valor=0;
public:
	MainMenuState();
	~MainMenuState() {};
	virtual string getStateID() { return "MainMenu"; }; // stringID
	void update();
	void handleEvents();
	void render();

	Entity* addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size = WIN_WIDTH/900);

	void Background(string file);

	void createButtons();
};

