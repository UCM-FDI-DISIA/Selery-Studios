#include "BeatEmUpState.h"

BeatEmUpState::BeatEmUpState(bool boss, string typeBoss) {
	random = &SDLUtils::instance()->rand();
	scale = WIN_WIDTH / 900;

	background_ = new Entity();
	background_->addComponent<Transform>(int(TRANSFORM_H), Vector2D(0,0), WIN_WIDTH, WIN_HEIGHT);
	background_->addComponent<Image>(int(IMAGE_H), &SDLUtils::instance()->images().at("airBackground"), 0, 0, 0, BACKGROUNDAIR_WIDTH_FRAME, BACKGROUNDAIR_HEIGHT_FRAME);
	addEntity(background_);

	player_ = new Entity();
	player_->setContext(this);
	trans_player_ = player_->addComponent<Transform>(TRANSFORM_H, Vector2D(PlayerPosition_X, PlayerPosition_Y), PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME, scale);
	player_->addComponent<Image>(int(IMAGE_H), &SDLUtils::instance()->images().at("Player_BEU_fire"), 7, 28, 0, PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME,"fire");
	player_->addComponent<JumpComponent>(JUMP_H);
	player_->addComponent<LifeComponent>(LIFECOMPONENT_H, 10, false, "fire", player_);
	player_->addComponent<ShadowComponent>(SHADOWCOMPONENT_H);
	in_ = player_->addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H);
	player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	player_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	player_->addComponent<LimitBEU>(LIMITBEU_H);
	player_->addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(90, 80), 1.2*PLAYERBEU_HEIGHT_FRAME / 3, PLAYERBEU_WIDTH_FRAME / 7);
	player_->addComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H, 30);
	addEntity(player_);

	if (!boss) {
		AddEnemies(3);
	}
	else if (boss && typeBoss == "water") {
		AddWaterBoss();
	}
	else if (boss && typeBoss == "earth") {
		AddEarthBoss();
	}
	else if (boss && typeBoss == "air") {
		AddAirBoss();
	}
	else if (boss && typeBoss == "fire") {
		AddFireBoss();
	}

	colManager_ = new ColManager(this);


}

void BeatEmUpState::AddEnemies(int n_enemies) {
	for (int i = 0; i < n_enemies; ++i) {
		int character = random->nextInt(0, 4);
		int type = random->nextInt(0, 4);
		Vector2D pos={ (float)random->nextInt(50,WIN_WIDTH - 80),(float)random->nextInt(50,WIN_HEIGHT - 50) };
		enemy_ = new Entity();
		if (character == 0) {

			//enemy_ = addEntity(new EnemyBEU(pos, player_, 10, "bat", getEnemyType(element)));
			animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "bat", player_);
		}
		else if (character == 1) {
			animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "skeleton", player_);
		}
		else if (character == 2) {
			animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "shroom", player_);
		}
		else {
			animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "goblin", player_);

		}
		animation_->changeState(AnimationEnemyBEUComponent::Moving);
		animation_->updateAnimation();

		enemy_->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, scale)->setDir(Vector2D(1, 0));
		enemy_->addComponent<Image>(IMAGE_H, animation_->getTexture(), animation_->getNFrames(), animation_->getNFrames(), 0, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT);
		enemy_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
		enemy_->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player_, animation_->getEnemy());
		enemy_->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE, true, animation_->getType(), enemy_);
		enemy_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, animation_->getOffset(), animation_->getColHeight(), animation_->getColWidth());
		enemy_->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, enemy_, player_);
		addEntity(enemy_);



		//en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
	}
}

void BeatEmUpState::AddWaterBoss() {
	Vector2D position = Vector2D(sdlutils().width()/2 , sdlutils().height()/2);

	Entity* waterBoss = addEntity();
	waterBoss->addComponent<Transform>(TRANSFORM_H, position, WATERBOSS_WIDTH*1.2, WATERBOSS_HEIGHT*1.2);
	waterBoss->addComponent<Image>(IMAGE_H, &sdlutils().images().at("waterBoss"), 6, 16, 0, WATERBOSS_WIDTH, WATERBOSS_HEIGHT);
	waterBoss->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
}

void BeatEmUpState::AddFireBoss() {

}

void BeatEmUpState::AddEarthBoss() {
	//Vector2D pos = { WIN_WIDTH , WIN_HEIGHT / 2 };
	Vector2D pos = { 200 , 200 };
	boss_ = new Entity();
	Transform* t = boss_->addComponent<Transform>(TRANSFORM_H, pos, EARTHBOSS_WIDTH * 2, EARTHBOSS_HEIGHT * 2);
	boss_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("GolemFase1"), 8, 58, 0, EARTHBOSS_WIDTH, EARTHBOSS_HEIGHT);
	boss_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(10, 10), (EARTHBOSS_HEIGHT * 2) - 20, (EARTHBOSS_WIDTH * 2) - 20);
	boss_->addComponent<MovementEarthBossComponent>(MOVEMENTEARTHBOSSCOMPONENT_H, player_);
	boss_->addComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	boss_->addComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H);
	addEntity(boss_);
}

void BeatEmUpState::AddAirBoss() {

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
		return "air";
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
	Manager::refresh();
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
