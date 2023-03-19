#pragma once
#include "GameState.h"
#include "../utils/Manager.h"
#include"../components/Transform.h"
#include "../components/SliderComponent.h"

class OptionsState : public GameState {
public:
	OptionsState();
private:
	void CreateInteractuableObjects();
};

