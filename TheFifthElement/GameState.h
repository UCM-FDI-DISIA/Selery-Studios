#pragma once
#include "StateManager.h"

class GameState :
    public StateManager
{
public:
    virtual string getStateID() { return "top-down"; }; // stringID
};

