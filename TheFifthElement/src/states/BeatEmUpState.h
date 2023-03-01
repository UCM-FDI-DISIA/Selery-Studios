#pragma once
#include "GameState.h"
#include "../Entities/Npc.h"
#include "../Entities/PlayerBEU.h"
#include "../Entities/Enemy.h"
#include "../components/InputComponent.h"
#include "../Entities/DialogBox.h"
#include "../Entities/EnemyBEU.h"
#include "../sdlutils/SDLUtils.h"
#include "../Entities/Background.h"

class BeatEmUpState	 : public Manager {
private:
	PlayerBEU* player_;
	InputComponentBEU* in_;
	bool dialog_;
public:
	string getStateID(); // stringID

	BeatEmUpState();

	void finishBEU();
	void handleEvents();
	~BeatEmUpState() {}
};

