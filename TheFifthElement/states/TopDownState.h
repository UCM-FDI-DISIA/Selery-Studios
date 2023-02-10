#pragma once
#include "GameState.h"
#include "../Npc.h"
class TopDownState: public Manager{
public:
    virtual string getStateID() { return "top-down"; }; // stringID
	TopDownState() {
		addEntity(new Npc());
	}
	~TopDownState() {

	}

};

