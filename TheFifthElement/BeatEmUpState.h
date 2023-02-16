#pragma once
#include "states/GameState.h"
#include "Npc.h"
#include "PlayerTD.h"
#include "Enemy.h"
#include "InputComponent.h"
#include "DialogBox.h"

class BeatEmUpState : public Manager
{

public:
	virtual string getStateID() { return "beat-em-up"; }; // stringID

	BeatEmUpState(GameManager* gm_) {
		Gm_ = gm_;
		player_ = new PlayerTD(Gm_);
		addEntity(new Npc(Gm_, player_));

		cmpId_type w = int(INPUTCOMPONENT_H);
		in_ = player_->getComponent<InputComponent>(w);
		addEntity(player_);
		addEntity(new DialogBox(Gm_));

		addEntity(new Enemy(Gm_, player_, 100));
	}

	void handleEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			in_->handleEvents(event);
			;
		}
	}
	~BeatEmUpState() {

	}
private:
	GameManager* Gm_;
	PlayerTD* player_;
	InputComponent* in_;

};

