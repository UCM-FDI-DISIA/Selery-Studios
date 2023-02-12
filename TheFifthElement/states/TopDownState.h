#pragma once
#include "GameState.h"
#include "../Npc.h"
#include "../PlayerTD.h"
#include "../Enemy.h"
class TopDownState : public Manager {
public:
	virtual string getStateID() { return "top-down"; }; // stringID
	TopDownState(GameManager* gm_) {
		Gm_ = gm_;
		addEntity(new Npc(Gm_));
		player_ = new PlayerTD(Gm_);
		addEntity(player_);
		addEntity(new Enemy(Gm_,player_));
	}
	~TopDownState() {

	}
private:
	GameManager* Gm_;
	PlayerTD* player_;
};

