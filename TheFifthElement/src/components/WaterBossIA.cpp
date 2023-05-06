#include "WaterBossIA.h"

WaterBossIA::WaterBossIA(Entity* player){
	currentState_ = NONE;
	player_ = player;
}

void WaterBossIA::initComponent() {
	wLife_ = ent_->getComponent<WaterBossLife>(WATERBOSSLIFE_H);
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	cont = 0;
	chrono = 3000;
	lastWave_ = nullptr;
	offset = 600; // a mas offset mas separacion entre cubos de hielo
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	downLimit = WIN_HEIGHT;
	topLimit = WIN_HEIGHT * 0.55;

	attackIcePos_ = WIN_WIDTH / 2 - (WATERBOSS_WIDTH)/ 2;
	attackWavesPos_ = WIN_WIDTH * 7 / 11;
	idlePos_ = (WIN_WIDTH * 3 / 4 - (WATERBOSS_WIDTH) / 2);

	iceCont_ = 0;// al principio el contador estar� a 0
}

void WaterBossIA::update() {
	if (currentState_ == NONE) {// no ataca
		if (!(abs(tr_->getPos().getX() - idlePos_) >= 3)) {
			setIdle();
			tr_->setDir(Vector2D(0,0));
			if(chrono <= sdlutils().currRealTime())	newAttack();
		}
	}
	else {
		// ataque olas
		if (currentState_ == WAVES) {
			
			// anda hasta el extremo de la pantalla
			if (!(abs(tr_->getPos().getX() - attackWavesPos_) >= 3)) { 
				tr_->setDir(Vector2D(0, 0));
				
				// animacion golpes
				im_->setFlip(SDL_FLIP_NONE);
				im_->setAnim("waterBoss_attack", 14, true);
				
				// espaciado entre olas
				if (lastWave_ == nullptr || lastWave_->getPos().getX() < (WIN_WIDTH - (ICEBLOCK_WIDTH * WIN_WIDTH / 900 + offset))) {
					summonWave();
					cont++;
					// numero de olas
					if (cont > 4) {
						currentState_ = NONE;
						chrono = sdlutils().currRealTime() + 3000;
						cont = 0;
						dir_ = Vector2D(idlePos_ - tr_->getPos().getX(), 0).normalize();
						tr_->setDir(dir_);
						setWalk(dir_);
					}
				}
			}
		}
		// ataque hielo
		else {
			if (!(abs(tr_->getPos().getX() - attackIcePos_) >= 3)) {
				if (!set_) {
					tr_->setDir(Vector2D(0, 0));// el boss se para
					fila_ = 5;
					im_->setAnim("waterBoss", 6, false, fila_);
					set_ = true;
				}

				if (fila_ == 5 && !im_->isAnimPlaying()) {
					fila_ = 6; 
					im_->setAnim("waterBoss", 16, false, fila_);
					iceCont_ = 10;
				}
				else if (fila_ == 6) {
					wLife_->setInvulnerable(false);
					if (!im_->isAnimPlaying()) {
						fila_ = 7; 
						//im_->setAnim("waterBoss", 4, false, fila_);
						im_->setAnim("waterBoss", 6, false, fila_);
					}
					else if (iceCont_ >= 10) {
						int rnd = rand() % 2;// n�mero de car�mbanos aleatorio entre 0 y 1
						addIce(rnd);
						iceCont_ == 0;
					}
					iceCont_++;
				}
				else if (fila_ == 7 && !im_->isAnimPlaying()) {
					wLife_->setInvulnerable(true);
					set_ = false;
					currentState_ = NONE;
					chrono = sdlutils().currRealTime() + 3000;
					cont = 0;
					dir_ = Vector2D(idlePos_ - tr_->getPos().getX(), 0).normalize();
					tr_->setDir(dir_);
					setWalk(dir_);
				}
			}
		}
	}
}

void WaterBossIA::newAttack() {
	int rnd_ = rand() % 2;
	if (rnd_ == 1) attackWaves();
	else attackIce();
}

void WaterBossIA::attackWaves(){
	currentState_ = WAVES;
	dir_ = Vector2D(attackWavesPos_ - tr_->getPos().getX(), 0).normalize();
	tr_->setDir(dir_);
	setWalk(dir_);
}

void WaterBossIA::attackIce() {
	currentState_ = ICE;
	dir_ = Vector2D(attackIcePos_ - tr_->getPos().getX(), 0).normalize();
	tr_->setDir(dir_);
	setWalk(dir_);
}

void WaterBossIA::setIdle() {
	fila_ = 0;
	im_->setFlip(SDL_FLIP_NONE);
	//im_->setAnim("waterBoss_idle", 6, false);
	im_->setAnim("waterBoss", 6, false, fila_);
	////im_->setAnim(false, 0, 6, 0, 6);
}

void WaterBossIA::setWalk(Vector2D dir) {
	fila_ = 1;
	if (dir.getX() > 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else im_->setFlip(SDL_FLIP_NONE);
	//im_->setAnim("waterBoss_walk", 10, false);
	im_->setAnim("waterBoss", 10, false, fila_);
	////im_->setAnim(false, 1, 10, 0, 10);
}

void WaterBossIA::summonWave() { // crea 2 olas
	
	int rnd_ = rand() % 3;
	if (rnd_ == 0) { // no arriba
		wavePos_ = topLimit + (downLimit - topLimit) * 1/3;
		createWave(wavePos_);
		wavePos_ = topLimit + (downLimit - topLimit) - (ICEBLOCK_HEIGHT* tr_->getSize());
	}
	else if (rnd_ == 1) { // no medio
		wavePos_ = topLimit;
		createWave(wavePos_);
		wavePos_ = topLimit + (downLimit - topLimit) -(ICEBLOCK_HEIGHT*tr_->getSize());
	}
	else { // no abajo
		wavePos_ = topLimit + (downLimit - topLimit) * 1/3;
		createWave(wavePos_);
		wavePos_ = topLimit;
	}
	lastWave_ = createWave(wavePos_)->getComponent<Transform>(TRANSFORM_H);
	sdlutils().soundEffects().at("iceBlock").play();
}

Entity* WaterBossIA::createWave(float y) {
	Vector2D pos = Vector2D(WIN_WIDTH, y);
	Entity* wave = mngr_->addEntity();
	if (WIN_WIDTH == 1920)wave->addComponent<Transform>(TRANSFORM_H, pos, ICEBLOCK_WIDTH, ICEBLOCK_HEIGHT, 1, 5)->setDir(Vector2D(-1, 0));
	else wave->addComponent<Transform>(TRANSFORM_H, pos, ICEBLOCK_WIDTH, ICEBLOCK_HEIGHT, 1, 4)->setDir(Vector2D(-1, 0));
	wave->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("iceBlock"), ICEBLOCK_WIDTH, ICEBLOCK_HEIGHT, 8);
	wave->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	wave->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), ICEBLOCK_HEIGHT, ICEBLOCK_WIDTH);
	wave->addComponent<DisableOnExit>(DISABLEONEXIT_H);
	wave->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, wave, player_);
	return wave;
}

void WaterBossIA::addIce(int n) {
	for (int i = 0; i < n; i++) {
		Entity* ice_ = new Entity();

		int size_ = 48; // cada car�mbano tiene un src de 48x48

		int rndX_ = rand() % (WIN_WIDTH - size_);
		int rndY_ = rand() % (WIN_HEIGHT/2); // position
		ice_->addComponent<Transform>(TRANSFORM_H, Vector2D(rndX_, rndY_), size_, size_, 0.7, 2);
		rndY_ += (WIN_HEIGHT/2 + size_);// shadow position

		ice_->addComponent<IceShadowComponent>(ICESHADOWCOMPONENT_H, Vector2D(rndX_, rndY_), 0.7, player_);
		
		ice_->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("ice"), size_, size_, 3);
		Vector2D offset = Vector2D(10, 0);
		ice_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, offset, size_/2, size_/2);
		ice_->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, ice_, player_);
		ice_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
		ice_->addComponent<IceIAComponent>(ICEIACOMPONENT_H, player_);


		mngr_->addEntity(ice_);
	}

}