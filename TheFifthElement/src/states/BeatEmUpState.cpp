#include "BeatEmUpState.h"


BeatEmUpState::BeatEmUpState() {
	player_ = new Entity();
	player_->setContext(this);
	trans_player_ = player_->addComponent<Transform>(TRANSFORM_H,Vector2D( PlayerPosition_X, PlayerPosition_Y), PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME);
	player_->addComponent<Image>(int(IMAGE_H), &SDLUtils::instance()->images().at("Player_BEU") , 7, 28, 0, PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME);
	player_->addComponent<JumpComponent>(JUMP_H);
	in_ = player_->addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H);
	player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	player_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	player_->addComponent<LimitBEU>(LIMITBEU_H);
	player_->addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(120, 70), PLAYERBEU_HEIGHT_FRAME / 2, PLAYERBEU_WIDTH_FRAME / 7);
	player_->getComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	addEntity(player_);

	background_ = new Entity();
	background_->addComponent<Transform>(int(TRANSFORM_H), Vector2D(0,0), WIN_WIDTH, WIN_HEIGHT);
	background_->addComponent<Image>(int(IMAGE_H), &SDLUtils::instance()->images().at("airBackground"), 0, 0, 0, BACKGROUNDAIR_WIDTH_FRAME, BACKGROUNDAIR_HEIGHT_FRAME);
	addEntity(background_);
	
	AddEnemies(3);

	

	colManager_ = new ColManager(this);

	
}
void BeatEmUpState::AddEnemies(int n_enemies) {
	for (int i = 0; i < n_enemies; ++i) {
		int character = random->nextInt(0, 4);
		int type = random->nextInt(0, 4);
		Vector2D pos={ (float)random->nextInt(50,WIN_WIDTH - 80),(float)random->nextInt(50,WIN_HEIGHT - 50) };
		if (character == 0) {
			
			//enemy_ = addEntity(new EnemyBEU(pos, player_, 10, "bat", getEnemyType(element)));
			animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "bat");
		}
		else if (character == 1) {
			animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "skeleton");
		}
		else if (character == 2) {
			animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "shroom");	
		}
		else {
			//en_ = addEntity(new EnemyBEU(pos, player_, 10, "goblin", getEnemyType(element)));
			animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "goblin");
		}
		animation_->changeState(AnimationEnemyBEUComponent::Moving);
		animation_->updateAnimation();

		enemy_->addComponent<Transform>(TRANSFORM_H, pos, animation_->Get_enemy_Width(), animation_->Get_enemy_Height());
		//enemy->addComponent<Image>(IMAGE_H, animation_->Get_enemy_Texture(), nframes_, nframes_, fila_, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT);
		enemy_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
		enemy_->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player_, animation_->Get_enemy());
		enemy_->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE, nullptr);
		//enemy->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, offset_, ColHeight_, ColWidth_);
		addEntity(enemy_);

		
	
		//en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
	}
}
string BeatEmUpState::getEnemyType(int i) {
	if (i == 0) {
		return "fire";
	}
	else if (i == 1) {
		return "water";
	}
	else if (i == 2) {
		return "earth";
	}
	else {
		return "wind";
	}

}
void BeatEmUpState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) { in_->handleEvents(event); }
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_V)) { finishBEU(); };
	
}

void BeatEmUpState::finishBEU() {
	GameManager::instance()->goTopDown();
	SDLUtils::instance()->soundEffects().at("Battle").haltChannel();
	
}

string BeatEmUpState::getStateID() {
	return "BeatEmUpState";
}

void BeatEmUpState::update() {
	/*Manager::refresh();*/
	Manager::update();
	camRect_.x = (trans_player_->getPos().getX() + camOffset_) - WIN_WIDTH / 2;
	camRect_.y = (trans_player_->getPos().getY() - WIN_HEIGHT / 2);
	// Clamp
	if (camRect_.x < 0) {
		camRect_.x = 0;
	}
	camRect_.y = 0;
	if (camRect_.x > (BACKGROUNDAIR_WIDTH_FRAME)) {
			camRect_.x = BACKGROUNDAIR_WIDTH_FRAME;
	}
}