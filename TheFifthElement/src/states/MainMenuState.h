#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/Button.h"
class MainMenuState : public Manager
{
private:
	Entity* playButton;
	Entity* exitButton;
	Entity* optionsButton;
	Image* im_;
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

