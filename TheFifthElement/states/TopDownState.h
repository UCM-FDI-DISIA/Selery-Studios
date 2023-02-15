#pragma once
#include "GameState.h"
#include "../Npc.h"
#include "../PlayerTD.h"
#include "../Enemy.h"
#include "../PlayerBEU.h"
#include "../InputComponent.h"
#include "../InputComponentBEU.h"
#include "../DialogBox.h"
#include "../Portal.h"


class TopDownState : public Manager {
public:
	virtual string getStateID() { return "top-down"; }; // stringID

	TopDownState(GameManager* gm_) {
		Gm_ = gm_;
		player_ = new PlayerTD(Gm_);

		addEntity(new Npc(Gm_, player_));
		playerBEU_ = new PlayerBEU(Gm_);

		cmpId_type b = int(INPUTCOMPONENTBEU_H);
		inBEU_ = playerBEU_->getComponent<InputComponentBEU>(b);
		cmpId_type w = int(INPUTCOMPONENT_H);
		in_ = player_->getComponent<InputComponent>(w);
		addEntity(player_);
		addEntity(playerBEU_);
		addEntity(new DialogBox(Gm_));
		addEntity(new Enemy(Gm_, player_, 100));
		addEntity(new Portal(Gm_, player_));
	}
	void handleEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			in_->handleEvents(event);
			inBEU_->handleEvents(event);
;		}
	}
	~TopDownState() {

	}
private:
	GameManager* Gm_;
	PlayerTD* player_;
	InputComponent* in_;
	PlayerBEU* playerBEU_;
	InputComponentBEU* inBEU_;
};

