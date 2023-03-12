#pragma once
#include "GameState.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Button.h"
//#include "../Entities/PlayerTD.h"
//#include "../Entities/PlayerBEU.h"
class PauseMenuState: public Manager {
private:
	virtual string getStateID() { return "PauseMenu"; }; // stringID
	Entity* resumeButton_;
	float resumeButtonWidth_, resumeButtonHeight_;
	Vector2D resumeButtonPos_;
	Vector2D buttonOffset_ = { 150,150 };
public:
	PauseMenuState();
	~PauseMenuState() {};

	void update();
	void handleEvents();
	void render();
};