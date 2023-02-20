#pragma once
#include "GameState.h"
#include "../Entities/Npc.h"
#include "../Entities/PlayerBEU.h"
#include "../Entities/Enemy.h"
#include "../components/InputComponent.h"
#include "../Entities/DialogBox.h"
#include "../Entities/EnemyBEU.h"
#include "../Entities/Background.h"
class BeatEmUpState	 : public Manager
{

public:
	virtual string getStateID() { return "beat-em-up"; }; // stringID

	BeatEmUpState(GameManager* gm_) {
		
		addEntity(new Background());
		Gm_ = gm_;
		player_ = addEntity(new PlayerBEU(Gm_));
		dialog_ = false;
		
		//playerBEU_ = new PlayerBEU(Gm_);

		cmpId_type b = int(INPUTCOMPONENTBEU_H);
		in_ = player_->getComponent<InputComponentBEU>(b);
		cmpId_type w = int(INPUTCOMPONENT_H);
		addEntity(new EnemyBEU(gm_, player_, 100));

	
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

