#pragma once
#include "GameState.h"
#include "../utils/Manager.h"
#include"../components/Transform.h"
#include "../components/SliderComponent.h"

class OptionsState : public Manager {
public:
	OptionsState();
<<<<<<< Updated upstream
=======
	~OptionsState() {};
	void Background(string file);
	void render();
	virtual string getStateID() { return "OptionsState"; }
	void update();
	void handleEvents();
	Entity* addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size);
	void createButtons();
>>>>>>> Stashed changes
private:
	void CreateInteractuableObjects();
};

