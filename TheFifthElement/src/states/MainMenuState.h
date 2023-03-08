#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/Button.h"
class MainMenuState: public Manager
{
private:
	virtual string getStateID() { return "MainMenu"; }; // stringID
	Entity* playButton;
	float playButtonWidth, playButtonHeight;
	Vector2D playButtonPos;
public:
	MainMenuState();
	~MainMenuState() {};

	void update();
	void handleEvents();
	void render();
};

