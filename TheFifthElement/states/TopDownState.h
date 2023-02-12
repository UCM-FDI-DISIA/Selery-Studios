#pragma once
#include "GameState.h"
#include "../Npc.h"
#include "../PlayerTD.h"

class TopDownState : public Manager {
public:
	virtual string getStateID() { return "top-down"; }; // stringID
	TopDownState(GameManager* gm_) {
		Gm_ = gm_;
		addEntity(new Npc(Gm_));
		//addEntity(new PlayerTD(Gm_));
	}
	~TopDownState() {

	}
private:
	GameManager* Gm_;
};

