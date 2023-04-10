#include "BeatEmUpState.h"
#include "../components/SkinBEUComponent.h"

BeatEmUpState::BeatEmUpState(bool Boss,Entity* enemySends, string typeBoss, int nEnemies, int timeGen) {
	enemySender = enemySends;
	numEnemies = nEnemies;
	timeToGenerate = timeGen;
	boss = Boss;

	SDLUtils::instance()->soundEffects().at("Battle").play();

	random = &SDLUtils::instance()->rand();

	background_ = new Entity();
	background_->addComponent<Transform>(TRANSFORM_H, Vector2D(0,0), BACKGROUNDBEU_WIDTH, WIN_HEIGHT);
	background_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("BEU_Background"));
	addEntity(background_);
	Hud_ = new Entity();
	Hud_->setContext(this);
	roulete = Hud_->addComponent<Roulette>(ROULETTECOMPONENT_H);

	player_ = new Entity();
	player_->setContext(this);
	trans_player_ = player_->addComponent<Transform>(TRANSFORM_H, Vector2D(PlayerPosition_X, PlayerPosition_Y), PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME, 2); //el ultimo numero sirve para multiplicar el tamaño del player
	sk_ = player_->addComponent<SkinBEUComponent>(SKINBEUCOMPONENT_H, "air");
	sk_->changeState(SkinBEUComponent::Idle);
	texture_player_ = &SDLUtils::instance()->images().at(sk_->getSkin());
	player_->addComponent<FramedImage>(FRAMEDIMAGE_H, texture_player_, PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME, 8, "air");
	player_->addComponent<JumpComponent>(JUMP_H);
	addEntity(Hud_);
	player_->addComponent<LifeComponent>(LIFECOMPONENT_H, props_->instance()->getLives(0));
	player_->addComponent<ShadowComponent>(SHADOWCOMPONENT_H);
	in_ = player_->addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H, roulete);
	player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	player_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	player_->addComponent<LimitBEU>(LIMITBEU_H);
	player_->addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(90, 80), 1.2*PLAYERBEU_HEIGHT_FRAME / 3, PLAYERBEU_WIDTH_FRAME / 7);
	player_->addComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H, 30, 10);
	sk_->initComponent();
	addEntity(player_);
	
	colManager_ = new ColManager(this);

	if (!boss) {
		//AddEnemies(3);
		//AddEnemy();
	}
	else if (boss && typeBoss == "water") {
		AddWaterBoss();
	}
	else if (boss && typeBoss == "earth") {
		AddEarthBoss();
	}
	else if (boss && typeBoss == "light") {
		AddLightBoss();
	}
	else if (boss && typeBoss == "fire") {
		AddFireBoss();
	}
}

void BeatEmUpState::AddEnemy() {
	int character = random->nextInt(0, 4);
	int type = random->nextInt(0, 4);
	int dist = 900 * (WIN_WIDTH / 900);
	Vector2D pos = { trans_player_->getPos().getX() + dist ,(float)random->nextInt(50,WIN_HEIGHT - 50) };
	enemy_ = new Entity();
	enemy_->setContext(this);
	if (character == 0) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "bat", player_);

	else if (character == 1) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "skeleton", player_);

	else if (character == 2) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "shroom", player_);

	else animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "goblin", player_);

	enemy_->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT)->setDir(Vector2D(1, 0));
	enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, animation_->getTexture(), ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, animation_->getNFrames(), getEnemyType(type));
	enemy_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	enemy_->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player_, animation_->getEnemy());
	enemy_->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE);
	enemy_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, animation_->getOffset(), animation_->getColHeight(), animation_->getColWidth());
	enemy_->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, enemy_, player_);
	animation_->initComponent();
	enemy_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);

	addEntity(enemy_);
}

void BeatEmUpState::AddEnemies(int n_enemies) {
	for (int i = 0; i < n_enemies; ++i) {
		numEnemies = n_enemies;
		int character = random->nextInt(0, 4);
		int type = random->nextInt(0, 4);
		Vector2D pos={ (float)random->nextInt(50,WIN_WIDTH - 80),(float)random->nextInt(50,WIN_HEIGHT - 50) };
		enemy_ = new Entity();
		enemy_->setContext(this);
		if (character == 0) animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "bat", player_);

		else if (character == 1) animation_=enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "skeleton", player_);

		else if (character == 2) animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "shroom", player_);

		else animation_ = enemy_->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, getEnemyType(type), "goblin", player_);

		
		////animation_->changeState(AnimationEnemyBEUComponent::Moving);
		////animation_->updateAnimation();

		enemy_->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT)->setDir(Vector2D(1, 0));
		enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, animation_->getTexture(), ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, animation_->getNFrames(), getEnemyType(type));
		enemy_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
		enemy_->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player_, animation_->getEnemy());
		enemy_->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE);
		enemy_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, animation_->getOffset(), animation_->getColHeight(), animation_->getColWidth());
		enemy_->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, enemy_, player_);
		animation_->initComponent();
		enemy_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
		
		addEntity(enemy_);
	}
}

void BeatEmUpState::AddWaterBoss() {
	Vector2D position = Vector2D(sdlutils().width() * 3 / 4 - WATERBOSS_WIDTH , sdlutils().height()/2);

	Entity* waterBoss = addEntity();
	waterBoss->addComponent<Transform>(TRANSFORM_H, position, WATERBOSS_WIDTH*1.2, WATERBOSS_HEIGHT*1.2);
	////waterBoss->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("waterBoss"), 6, 16, 0, WATERBOSS_WIDTH, WATERBOSS_HEIGHT);
	waterBoss->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("waterBoss"), WATERBOSS_WIDTH, WATERBOSS_HEIGHT, 16, "water");
	waterBoss->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	waterBoss->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(70, 10), WATERBOSS_HEIGHT, WATERBOSS_WIDTH/2);
	waterBoss->addComponent<WaterBossIA>(WATERBOSSIA_H, player_);
	waterBoss->addComponent<WaterBossLife>(WATERBOSSLIFE_H, 100);
	// buscar assets olas
}

void BeatEmUpState::AddFireBoss() {

}

void BeatEmUpState::AddEarthBoss() {
	//Vector2D pos = { WIN_WIDTH , WIN_HEIGHT / 2 };
	Vector2D pos = { 200 , 200 };
	boss_ = new Entity();
	boss_->setContext(this);
	Transform* t = boss_->addComponent<Transform>(TRANSFORM_H, pos, EARTHBOSS_WIDTH * 2, EARTHBOSS_HEIGHT * 2);
	boss_->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("GolemFase1_idle"), EARTHBOSS_WIDTH, EARTHBOSS_HEIGHT, 8, "earth");
	boss_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(150, 120), (EARTHBOSS_HEIGHT * 2) - 240, (EARTHBOSS_WIDTH * 2) - 300);
	boss_->addComponent<PointOfFightComponent>(POINTOFFIGHTCOMPONENT_H, 60, 140);
	boss_->addComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	boss_->addComponent<MovementEarthBossComponent>(MOVEMENTEARTHBOSSCOMPONENT_H, player_);
	boss_->addComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H);
	boss_->addComponent<AttackEarthBossComponent>(ATTACKEARTHBOSSCOMPONENT_H);
	boss_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	
	addEntity(boss_);
}

void BeatEmUpState::AddLightBoss() 
{
	//AddEnemies(5);
	numEnemies = 1;
	Entity* lightBoss = new Entity();
	lightBoss->setContext(this);
	lightBoss->addComponent<Transform>(TRANSFORM_H, Vector2D(700, WIN_HEIGHT/2), LIGHTBOSS_WIDTH, LIGHTBOSS_HEIGHT);
	lightBoss->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("BEULightBossIdle"), LIGHTBOSS_WIDTH, LIGHTBOSS_HEIGHT, 12, "light");
	lightBoss->addComponent<MovementLightBossComponent>(MOVEMENTLIGHTBOSSCOMPONENT_H, player_);
	lightBoss->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), LIGHTBOSS_HEIGHT, LIGHTBOSS_WIDTH);
	lightBoss->addComponent<AttackLightBossComponent>(ATTACKLIGHTBOSSCOMPONENT_H, player_);
	//animation
	lightBoss->addComponent<LifeLightBossComponent>(LIFELIGHTBOSSCOMPONENT_H);
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
	while (SDL_PollEvent(&event)) { in_->handleEvents(event); }
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_V)) { finishBEU(); };

}

void BeatEmUpState::finishBEU() {
	numEnemies -= 1;
	if (numEnemies <= 0)
	{
		Saving::instance()->deletePos();
		SDLUtils::instance()->soundEffects().at("Battle").haltChannel();
		GameManager::instance()->goTopDown();
		
		enemySender->~Entity();
	}
}

string BeatEmUpState::getStateID() {
	return "BeatEmUpState";
}

void BeatEmUpState::update() {
	Manager::refresh();
	Manager::update();
	
	if (!boss && createdEnemies < numEnemies && cont <= 0) { //aqui salta un fallo porque esta leyendo numenemies que no es fijo, se reduce cuando matas a un enemigo y si matas a un enemigo antes de que se genere otro dejan de generarse
		AddEnemy();
		cont = timeToGenerate;
		createdEnemies++;
	}
	cont--;

	camRect_.x = camRect_.x + ((trans_player_->getPos().getX() + camOffset_ - camRect_.x) - WIN_WIDTH / 2) * 0.05;
	camRect_.y = 0;
	// Clamp de la cámara
	if (camRect_.x < 0) {
		camRect_.x = 0;
	}	
	else if (camRect_.x > BACKGROUNDBEU_WIDTH - WIN_WIDTH) {
		camRect_.x = BACKGROUNDBEU_WIDTH - WIN_WIDTH;
	}
}
