#pragma once
#include "GameState.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
#include "../components/Image.h"
//#include "../Entities/PlayerTD.h"
//#include "../Entities/PlayerBEU.h"
class PauseMenuState: public Manager {
private:
	Entity* resumeButton_;
	float resumeButtonWidth_, resumeButtonHeight_;
	Vector2D resumeButtonPos_;
	Vector2D buttonOffset_ = { 150,150 };

	Entity* resumeButton;
	Entity* menuButton;
	Entity* optionsButton;
	Image* im_;
public:
	PauseMenuState();
	~PauseMenuState() {};
	virtual string getStateID() { return "PauseMenu"; }; // stringID

	void update();
	void handleEvents();
	void render();

	Entity* addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size = WIN_WIDTH / 900);
	void Background(string file);
	void createButtons();
};