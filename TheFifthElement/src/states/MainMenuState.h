#pragma once
#include "GameState.h"
#include "../Entities/Npc.h"
#include "../Entities/PlayerTD.h"
#include "../Entities/Enemy.h"
#include "../Entities/PlayerBEU.h"
#include "../components/InputComponent.h"
#include "../components/InputComponentBEU.h"
#include "../Entities/DialogBox.h"
#include "../Entities/Portal.h"
#include "../Entities/Element.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/Camera.h"
#include "../Entities/RedirectTile.h"
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

