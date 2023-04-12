#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
#include "../components/sliderComponent.h"
#include "../components/FramedImage.h"

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
	Entity* createCharacter(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size);
	void deleteButtonsTD();
	void deleteButtonsBEU();
	void exitControls();
	void ControlsBackground(string file);
private:
	Entity* backButton;
	Entity* muteButton;
	Entity* TDcontrolsButton;
	Entity* BEUcontrolsButton;
	Entity* sliderBrillo;
	Entity* sliderSonido;
	Entity* exitControlsButton;
	Entity* resumeButton;
	Image* im_;
	bool exitActive=false;
	string controls;
};
