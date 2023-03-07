#include "BeatEmUpState.h"


BeatEmUpState::BeatEmUpState() {
	player_ = new Entity();
	player_->setContext(this);
	trplayer_ = player_->addComponent<Transform>(TRANSFORM_H,Vector2D( PlayerPosition_X, PlayerPosition_Y), PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME);
	player_->addComponent<Image>(int(IMAGE_H), &SDLUtils::instance()->images().at("Player_BEU") , 7, 28, 0, PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME);
	player_->addComponent<JumpComponent>(JUMP_H);
	in_ = player_->addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H);
	player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	player_->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	player_->addComponent<LimitBEU>(LIMITBEU_H);
	player_->addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(120, 70), PLAYERBEU_HEIGHT_FRAME / 2, PLAYERBEU_WIDTH_FRAME / 7);
	addEntity(player_);

	background_ = new Entity();
	Vector2D v = { 0,0 };
	background_->addComponent<Transform>(int(TRANSFORM_H), v, WIN_WIDTH, WIN_HEIGHT,);
	Texture* t = &SDLUtils::instance()->images().at(file);
	background_->addComponent<Image>(int(IMAGE_H), t, f, f, f, BACKGROUNDAIR_WIDTH_FRAME, BACKGROUNDAIR_HEIGHT_FRAME);
	addEntity(new Background("airBackground"));
	player_ = addEntity(new PlayerBEU());
	dialog_ = false;
	r = &SDLUtils::instance()->rand();

	cmpId_type b = int(INPUTCOMPONENTBEU_H);
	in_ = player_->getComponent<InputComponentBEU>(b);
	cmpId_type w = int(INPUTCOMPONENT_H);
	//en_ = addEntity(new EnemyBEU(Vector2D(0, 0), player_, 3, "bat", "fire"));
	////addEntity(new EnemyBEU(Vector2D(110, 0), player_, 3, "bat", "fire"));
	//lb_ = addEntity(new LifeBar(3, "earth", en_));
	//en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);

	AddEnemies(3);

	atk_ = player_->getComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);

	/*n_enemies = 1;
	AddEnemies(n_enemies);*/
	colMan_ = new ColManager(this);
	//en_->addComponent<LifeComponent>(LIFECOMPONENT_H, 3, lb_)->subLife(3);
	/*SDLUtils::instance()->soundEffects().at("Battle").play();*/

	

	atk_->setContext(player_, this);

	
}
void BeatEmUpState::AddEnemies(int n_enemies) {
	for (int i = 0; i < n_enemies; ++i) {
		int character = r->nextInt(0, 4);

		int element = r->nextInt(0, 4);
		Vector2D pos={ (float)r->nextInt(50,WIN_WIDTH - 80),(float)r->nextInt(50,WIN_HEIGHT - 50) };
		if (character == 0) {
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "bat", getEnemyType(element)));
		}
		else if (character == 1) {
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "skeleton", getEnemyType(element)));
		}
		else if (character == 2) {
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "shroom", getEnemyType(element)));
		}
		else {
			en_ = addEntity(new EnemyBEU(pos, player_, 10, "goblin", getEnemyType(element)));
			
		}

		lb_ = addEntity(new LifeBar(10, getEnemyType(element), en_));
		en_->getComponent<LifeComponent>(LIFECOMPONENT_H)->setLifeBar(lb_);
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
	while (SDL_PollEvent(&event))
	{
		in_->handleEvents(event);
		
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_V)) {
			finishBEU();
		}
}

void BeatEmUpState::finishBEU() {
	GameManager::instance()->goTopDown();
	SDLUtils::instance()->soundEffects().at("Battle").haltChannel();
	cout << "si";
}

string BeatEmUpState::getStateID() {
	return "BeatEmUpState";
}

void BeatEmUpState::update() {
	/*Manager::refresh();*/
	Manager::update();
	camRect_.x = (player_->getComponent<Transform>(TRANSFORM_H)->getPos().getX() + camOffset_) - WIN_WIDTH / 2;
	camRect_.y = (player_->getComponent<Transform>(TRANSFORM_H)->getPos().getY()) - WIN_HEIGHT / 2;
	// Clamp
	if (camRect_.x < 0) {
		camRect_.x = 0;
	}
	camRect_.y = 0;
	if (camRect_.x > (BACKGROUNDAIR_WIDTH_FRAME)) {
			camRect_.x = BACKGROUNDAIR_WIDTH_FRAME;
	}
}