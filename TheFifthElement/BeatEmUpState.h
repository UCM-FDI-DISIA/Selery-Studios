#pragma once
#include "states/GameState.h"
#include "Npc.h"
#include "PlayerBEU.h"
#include "Enemy.h"
#include "InputComponent.h"
#include "DialogBox.h"

class BeatEmUpState : public Manager
{

public:
	virtual string getStateID() { return "beat-em-up"; }; // stringID

	BeatEmUpState(GameManager* gm_) {
		
		Gm_ = gm_;
		player_ = addEntity(new PlayerBEU(Gm_));
		dialog_ = false;
		
		//playerBEU_ = new PlayerBEU(Gm_);

		cmpId_type b = int(INPUTCOMPONENTBEU_H);
		in_ = player_->getComponent<InputComponentBEU>(b);
		cmpId_type w = int(INPUTCOMPONENT_H);
		

	
	}

	void handleEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			in_->handleEvents(event);
			
		}
	}
	~BeatEmUpState() {

	}
private:
	GameManager* Gm_;
	PlayerBEU* player_;
	InputComponentBEU* in_;
	bool dialog_;

};

