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
#include "../Entities/NewEntity.h"
class MainMenuState: public Manager
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

	//void addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size = WIN_WIDTH/900);
};

