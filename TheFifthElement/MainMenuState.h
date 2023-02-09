#pragma once
#include "StateManager.h"

class MainMenuState :
    public StateManager
{
public:
    virtual string getStateID() { return "MainMenu"; }; // stringID
};

