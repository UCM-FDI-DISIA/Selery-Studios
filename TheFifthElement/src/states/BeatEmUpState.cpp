#include "BeatEmUpState.h"
#include "../components/SkinBEUComponent.h"
#include "../Elements.h"
#include "../Game.h"

BeatEmUpState::BeatEmUpState(bool Boss,Entity* enemySends, string typeBoss, int nEnemies, int timeGen) {
	enemySender = enemySends;
	numEnemies = 0;
	lockCameraX = false;
	boss = Boss;
	fireBossBackgroundWidth = sdlutils().images().at("fondoBossFire").width();
	typeBoss_ = typeBoss;
	//sdlutils().soundEffects().at("Battle").play(-1);
	random = &sdlutils().rand();
	timeNextGeneration = sdlutils().currRealTime() + delayGenerateEnemies;

	//BACKGROUND
	background_ = new Entity();
	if (typeBoss == "water") {
		//background_->addComponent<Transform>(TRANSFORM_H, Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT);
		//background_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("fondoBossAgua"));
		Background("fondoBossAgua");// fondo estático
	}
	else if (typeBoss_ == "fire") {
		lockCameraX = true;
		Background("fondoBossFire");
	}
	else if (typeBoss_ == "light") {
		Background("fondoBossLight");
	}
	else {
		if (WIN_WIDTH == 1920) background_->addComponent<Transform>(TRANSFORM_H, Vector2D(0, 0), WIN_WIDTH, 600, 1);
		else background_->addComponent<Transform>(TRANSFORM_H, Vector2D(0, 0), BACKGROUNDBEU_WIDTH, WIN_HEIGHT, 1);
		background_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("BEU_Background"));
	}
	addEntity(background_);

	//HUD
	Hud_ = new Entity();
	Hud_->setContext(this);
	roulete = Hud_->addComponent<Roulette>(ROULETTECOMPONENT_H);

	//PLAYER
	player_ = new Entity();
	player_->setContext(this);
	trans_player_ = player_->addComponent<Transform>(TRANSFORM_H, Vector2D(PlayerPosition_X, PlayerPosition_Y), PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME, 2);
	sk_ = player_->addComponent<SkinBEUComponent>(SKINBEUCOMPONENT_H, "air");
	sk_->changeState(SkinBEUComponent::Idle);
	texture_player_ = &SDLUtils::instance()->images().at(sk_->getSkin());
	player_->addComponent<FramedImage>(FRAMEDIMAGE_H, texture_player_, PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME, 8, "air");
	player_->addComponent<JumpComponent>(JUMP_H);
	addEntity(Hud_);
	player_->addComponent<LifeComponent>(LIFECOMPONENT_H, props_->instance()->getLives(0), roulete);
	player_->addComponent<ShadowComponent>(SHADOWCOMPONENT_H);
	in_ = player_->addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H, roulete);
	player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	player_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	if (typeBoss == "water"|| typeBoss=="fire") player_->addComponent<LimitBEU>(LIMITBEU_H, true);
	else player_->addComponent<LimitBEU>(LIMITBEU_H);

	player_->addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(90, 80), PLAYERBEU_HEIGHT_FRAME, PLAYERBEU_WIDTH_FRAME);
	player_->addComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H, 30, 10);
	PowerUpControler* puCtrl = player_->addComponent<PowerUpControler>(POWERUPCTRL_H);
	properties().setPowerUpRef(puCtrl);
	sk_->initComponent();
	addEntity(player_);
	
	colManager_ = new ColManager(this);

	if (!boss) {
		AddEnemies(3);
	}
	else if (boss && typeBoss == "water") {
		AddWaterBoss();
	}
	else if (boss && typeBoss == "earth") {
		sdlutils().soundEffects().at("golemStarts").play();
		AddEarthBoss();
	}
	else if (boss && typeBoss == "light") {
		AddLightBoss();
	}
	else if (boss && typeBoss == "fire") {
		AddFireBoss();
	}
}

void BeatEmUpState::update() {
	Manager::refresh();
	Manager::update();
	colManager_->update();

	if (!boss && timeNextGeneration <= sdlutils().currRealTime()) {
		AddEnemy();
		timeNextGeneration = sdlutils().currRealTime() + delayGenerateEnemies;
	}

	if (!lockCameraX) {
		camRect_.x = (trans_player_->getPos().getX() + camOffset_) - WIN_WIDTH / 2;
		camRect_.x = camRect_.x + ((trans_player_->getPos().getX() + camOffset_ - camRect_.x) - WIN_WIDTH / 2) * 0.05;
		camRect_.y = 0;
	}

	if (camRect_.x < 0 || typeBoss_ == "water") {
		camRect_.x = 0;
	}
	if (Shakemyass) {
		camRect_.x += 10;
		Shakemyass = false;
	}
	else if (camRect_.x > BACKGROUNDBEU_WIDTH - WIN_WIDTH) {
		camRect_.x = BACKGROUNDBEU_WIDTH - WIN_WIDTH;
	}

	if (typeBoss_ == "fire") {
		
		float minX = -350.0f; 
		float maxX = fireBossBackgroundWidth + minX + WIN_WIDTH; 

		Vector2D playerPos = trans_player_->getPos();

		playerPos.setX(std::max(minX, std::min(playerPos.getX(), maxX)));

		trans_player_->setPos(playerPos);
	}



}


void BeatEmUpState::AddEnemies(int n_enemies) {
	for (int i = 0; i < n_enemies; ++i) {
		int character = 2;
		int type = 2;
		Vector2D pos={ (float)random->nextInt(50,WIN_WIDTH - 80),(float)random->nextInt(50,WIN_HEIGHT - 50) };
		
		enemy_ = addEntity();

		if (character == 0) animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "bat", player_);

		else if (character == 1) animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "skeleton", player_);

		else if (character == 2) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "shroom", player_);

		else animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "goblin", player_);

		enemy_->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT,2)->setDir(Vector2D(1, 0));
		enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, animation_->getTexture(), ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, animation_->getNFrames(), getEnemyType(type));
		enemy_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
		enemy_->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player_, animation_->getEnemy());
		enemy_->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE);
		enemy_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, animation_->getOffset(), animation_->getColHeight(), animation_->getColWidth());
		enemy_->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, enemy_, player_);
		animation_->initComponent();
		enemy_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);		

		++numEnemies;
	}
}

void BeatEmUpState::AddEnemy() {
	int character = 2;
	int type = 2;
	int dist = 900 * (WIN_WIDTH / 900);
	Vector2D pos = { trans_player_->getPos().getX() + dist ,(float)random->nextInt(50,WIN_HEIGHT - 50) };

	enemy_ = addEntity();

	if (character == 0) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "bat", player_);

	else if (character == 1) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "skeleton", player_);

	else if (character == 2) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "shroom", player_);

	else animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "goblin", player_);

	enemy_->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, 2)->setDir(Vector2D(1, 0));
	enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, animation_->getTexture(), ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, animation_->getNFrames(), getEnemyType(type));
	enemy_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	enemy_->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player_, animation_->getEnemy());
	enemy_->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE);
	enemy_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, animation_->getOffset(), animation_->getColHeight(), animation_->getColWidth());
	enemy_->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, enemy_, player_);
	animation_->initComponent();
	enemy_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);

	++numEnemies;
}

void BeatEmUpState::AddWaterBoss() {
	numEnemies = 1;
	Vector2D position = Vector2D(sdlutils().width() * 3 / 4 - (WATERBOSS_WIDTH) / 2, sdlutils().height()/2);

	Entity* waterBoss = addEntity();
	waterBoss->addComponent<Transform>(TRANSFORM_H, position, WATERBOSS_WIDTH, WATERBOSS_HEIGHT, 2.4);
	////waterBoss->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("waterBoss"), 6, 16, 0, WATERBOSS_WIDTH, WATERBOSS_HEIGHT);
	waterBoss->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("waterBoss"), WATERBOSS_WIDTH, WATERBOSS_HEIGHT, 16, 0, "water");
	waterBoss->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	waterBoss->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(50, 10), WATERBOSS_HEIGHT, WATERBOSS_WIDTH/2);
	waterBoss->addComponent<WaterBossLife>(WATERBOSSLIFE_H, 30);
	waterBoss->addComponent<WaterBossIA>(WATERBOSSIA_H, player_);
}

void BeatEmUpState::AddFireBoss() {
	numEnemies = 4; // Boss + enemigos que spawnea
	Vector2D pos = { WIN_WIDTH / 2+(FIREBOSS_WIDTH*1.8),WIN_HEIGHT - (FIREBOSS_HEIGHT*1.8+250) };
	Entity* boss = addEntity();
	Transform* t = boss->addComponent<Transform>(TRANSFORM_H, pos, FIREBOSS_WIDTH*1.8, FIREBOSS_HEIGHT*1.8);
	boss->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("FireBoss"),  FIREBOSS_WIDTH, FIREBOSS_HEIGHT,6,0, "FireBoss");
	boss->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	boss->addComponent<FireBossComponent>(FIREBOSSCOMPONENT_H, player_);
	boss->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(400, 100), (FIREBOSS_WIDTH * 1.8 / 2 - 25), (FIREBOSS_HEIGHT * 1.8 - 145));
	//boss->addComponent<LimitBEU>(LIMITBEU_H);
}

void BeatEmUpState::AddEarthBoss() {
	numEnemies = 1; 
	double upperLimit = WIN_HEIGHT / 4; // Define el límite superior
	double lowerLimit = WIN_HEIGHT / 2;
	//Vector2D pos = { WIN_WIDTH , WIN_HEIGHT / 2 };
	Vector2D pos = Vector2D(sdlutils().width() * 3 / 4 - WATERBOSS_WIDTH, sdlutils().height() / 2);
	earthBoss_ = new Entity();
	earthBoss_->setContext(this);
	Transform* t = earthBoss_->addComponent<Transform>(TRANSFORM_H, pos, EARTHBOSS_WIDTH * 2, EARTHBOSS_HEIGHT * 2);
	earthBoss_->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("GolemFase1_idle"), EARTHBOSS_WIDTH, EARTHBOSS_HEIGHT, 8, "EarthBoss");
	earthBoss_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(150, 120), (EARTHBOSS_HEIGHT * 2) - 240, (EARTHBOSS_WIDTH * 2) - 300);
	earthBoss_->addComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H, 60, 140);
	AnimationEarthBossComponent* earthAnim = earthBoss_->addComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	earthBoss_->addComponent<MovementEarthBossComponent>(MOVEMENTEARTHBOSSCOMPONENT_H, player_, upperLimit, lowerLimit);
	earthBoss_->addComponent<AttackEarthBossComponent>(ATTACKEARTHBOSSCOMPONENT_H);
	earthBoss_->addComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H);
	earthBoss_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);

	addEntity(earthBoss_);
}

void BeatEmUpState::AddLightBoss() {
	//AddEnemies(5);

	numEnemies = 1;
	Entity* lightBoss = new Entity();
	lightBoss->setContext(this);
	lightBoss->addComponent<Transform>(TRANSFORM_H, Vector2D(700, WIN_HEIGHT/2), LIGHTBOSS_WIDTH, LIGHTBOSS_HEIGHT);
	lightBoss->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("BEULightBossIdle"), LIGHTBOSS_WIDTH, LIGHTBOSS_HEIGHT, 12, "light");
	lightBoss->addComponent<MovementLightBossComponent>(MOVEMENTLIGHTBOSSCOMPONENT_H, player_);
	lightBoss->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(LIGHTBOSS_WIDTH/2 -20, LIGHTBOSS_HEIGHT/2), 64, 60);
	lightBoss->addComponent<AnimationLightBossComponent>(ANIMATIONLIGHTBOSSCOMPONENT_H);
	lightBoss->addComponent<AttackLightBossComponent>(ATTACKLIGHTBOSSCOMPONENT_H,player_);
	lightBoss->addComponent<LifeLightBossComponent>(LIFELIGHTBOSSCOMPONENT_H);
	//animation
	//attack box y point of fight ns
	addEntity(lightBoss);
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
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT ) {
			GameManager::instance()->getGame()->setExit(true);
		}
		in_->handleEvents(event); 
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_V)) { finishBEU(); };
}

void BeatEmUpState::finishBEU() {
	numEnemies -= 1;
	if (numEnemies <= 0) {		
		// DESBLOQUEO DE PERSONAJES
		if (boss) {
			if (typeBoss_ == "water") Elements::instance()->setWater();
			else if (typeBoss_ == "earth") Elements::instance()->setEarth();
			else if (typeBoss_ == "fire") Elements::instance()->setFire();
			if (typeBoss_ == "light") {
				trans_player_->setPos(Vector2D(0,0));
				GameManager::instance()->goToEndState();
			}
			props_->instance()->addMoney(200); // monedas ganadas al derrotar un boss
		}
		else {
			props_->instance()->addMoney(50); // monedas ganadas al derrotar non-bosses
			Quests::instance()->completedQuest("enemigos");
		}
		Saving::instance()->deletePos();
		SDLUtils::instance()->soundEffects().at("Battle").haltChannel();
		if( typeBoss_!= "light")
		GameManager::instance()->goTopDown();
		
		if (enemySender != nullptr)enemySender->~Entity();
	}
}

string BeatEmUpState::getStateID() {
	return "BeatEmUpState";
}

void BeatEmUpState::Background(string file) {
	Entity* e = new Entity();
	//e->setContext(this);
	int f = 0;
	bool matrix = false;
	Vector2D v = { 0,0 };
	int r = 0;
	//if(WIN_WIDTH == 1920)e->addComponent<Transform>(TRANSFORM_H, v, WIN_WIDTH/2, WIN_HEIGHT, 1);
	//else e->addComponent<Transform>(TRANSFORM_H, v, WIN_WIDTH, WIN_HEIGHT, 1);
	e->addComponent<Transform>(TRANSFORM_H, v, 900,600, 1);
	Texture* t = &SDLUtils::instance()->images().at(file);
	e->addComponent<Image>(IMAGE_H, t);
	addEntity(e);
}


void BeatEmUpState::ShakeCam(bool shakeyourbooty) {
	//Aplicar temblor de pantalla.
	
	//if (typeBoss_ == "water" || typeBoss_ == "fire") camRect_.x = 20;
	assert(this != nullptr);
	Shakemyass = shakeyourbooty;
}