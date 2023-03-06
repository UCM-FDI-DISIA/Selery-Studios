#include "BeatEmUpState.h"


BeatEmUpState::BeatEmUpState() {
	player_ = new Entity();
	player_->setContext(this);
	trplayer_ = player_->addComponent<Transform>(TRANSFORM_H, PlayerPosition_, PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME);
	sk_ = player_->addComponent<SkinComponent>(SKINCOMPONENT_H, "air");
	sk_->changeState(SkinComponent::Idle);
	sk_->changeMov();
	playerImage_ = player_->addComponent<Image>(IMAGE_H, tplayer_, PLAYERTD_NUMFRAMES, PLAYERTD_NUMFRAMES, 0, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME);
	player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	in_ = player_->addComponent<InputComponent>(INPUTCOMPONENT_H);
	addEntity(player_);

	t = new Texture(GameManager::instance()->getRenderer(), "./assets/Player/BeatEmUp/Fire/spritesheets/fireMatrix.png");
	//cmpId_type x = int(RENDERCOMPONENT_H);
	//referencia al texture y al transform
	fila_ = 0;

	addComponent<Image>(int(IMAGE_H), t, nframes, framesT_, fila_, PLAYERBEU_WIDTH_FRAME, PLAYERBEU_HEIGHT_FRAME);
	addComponent<JumpComponent>(JUMP_H);

	//igualamos el inputComponent a una variable ya que este necesita una referencia de image que a�n no existe, por lo que esa referencia es NULL
	in_ = addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H);
	addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	//addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(100, 100), 20, 20);
	addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	addComponent<LimitBEU>(LIMITBEU_H);

	//Al hacer aquí initComponent la referencia ya es correcta
	in_->initComponent();
	addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(120, 70), PlayerHeigth_ / 2, PlayerWidth_ / 7);

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