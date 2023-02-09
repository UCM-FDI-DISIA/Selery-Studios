#pragma once
#include "GameState.h"

class MainMenuState :public GameState
{
public:
    virtual string getStateID() { return "MainMenu"; }; // stringID
};

