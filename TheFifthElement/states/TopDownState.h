#pragma once
#include "GameState.h"

class TopDownState: public GameState{
public:
    virtual string getStateID() { return "top-down"; }; // stringID
   TopDownState() {

    }
};

