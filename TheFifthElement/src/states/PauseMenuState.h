#pragma once
#include "GameState.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/Button.h"
//#include "../Entities/PlayerTD.h"
//#include "../Entities/PlayerBEU.h"
class PauseMenuState: public Manager {
private:
	virtual string getStateID() { return "PauseMenu"; }; // stringID
	Entity* resumeButton_;
	Entity* mainMenuButton_;
	float resumeButtonWidth_, resumeButtonHeight_, mainMenuButtonWidth_, mainMenuButtonHeight_;
	Vector2D resumeButtonPos_, mainMenuButtonPos_;
public:
	PauseMenuState();
	~PauseMenuState() {};

	void update();
	void handleEvents();
	void render();
};