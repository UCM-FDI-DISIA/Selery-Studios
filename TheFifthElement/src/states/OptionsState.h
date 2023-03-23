
#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
#include "../components/sliderComponent.h"

class OptionsState : public Manager {
public:
	OptionsState();
	~OptionsState() {};
	virtual string getStateID() { return "OptionsState"; }
	void Background(string file);
	void render();
	void update();
	void handleEvents();
	Entity* addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size);
	void createButtons();
private:
	Entity* backButton;
	Entity* muteButton;
	Entity* controlsButton;
	Entity* sliderBrillo;
	Entity* sliderSonido;
	Image* im_;
};
