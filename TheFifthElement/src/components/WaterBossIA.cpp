#include "WaterBossIA.h"

WaterBossIA::WaterBossIA(Entity* player){
	currentState_ = NONE;
	player_ = player;
	attackIcePos_ = WIN_WIDTH / 2 - WATERBOSS_WIDTH / 2;
	attackWavesPos_ = WIN_WIDTH * 9 / 11;
}

void WaterBossIA::initComponent() {
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	cont = 0;
	chrono = 3000;
	lastWave_ = nullptr;
	offset = 150;
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	downLimit = sdlutils().height() - 100;
	topLimit = sdlutils().height()* 0.38;
}

void WaterBossIA::update() {
	if (currentState_ == NONE) {// no ataca
		if (!(abs(tr_->getPos().getX() - (WIN_WIDTH * 3 / 4 - WATERBOSS_WIDTH)) >= 3)) {
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
				////im_->setAnim(true, 2, 14, 0, 14); 
				
				// espaciado entre olas
				if (lastWave_ == nullptr || lastWave_->getPos().getX() < WIN_WIDTH - WAVE_WIDTH - offset) {
					summonWave();
					cont++;
					// numero de olas
					if (cont > 1) {
						currentState_ = NONE;
						chrono = sdlutils().currRealTime() + 3000;
						cont = 0;
						dir_ = Vector2D((WIN_WIDTH * 3 / 4 - WATERBOSS_WIDTH) - tr_->getPos().getX(), 0).normalize();
						tr_->setDir(dir_);
						setWalk(dir_);
					}
				}
			}
		}
		// ataque hielo
		else {
			if (!(abs(tr_->getPos().getX() - attackIcePos_) >= 3)) {
				setIdle();
				tr_->setDir(Vector2D(0, 0));
			}
		}
	}
}

void WaterBossIA::newAttack() {
	int rnd_ = rand() % 1;
	if (rnd_ == 0) attackWaves();
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
	im_->setFlip(SDL_FLIP_NONE);
	im_->setAnim("waterBoss_idle", 6, false);
	////im_->setAnim(false, 0, 6, 0, 6);
}

void WaterBossIA::setWalk(Vector2D dir) {
	if (dir.getX() > 0) im_->setFlip(SDL_FLIP_HORIZONTAL);
	else im_->setFlip(SDL_FLIP_NONE);
	im_->setAnim("waterBoss_walk", 10, false);
	////im_->setAnim(false, 1, 10, 0, 10);
}

void WaterBossIA::summonWave() { // crea 2 olas
	
	int rnd_ = rand() % 3;
	if (rnd_ == 0) { // no arriba
		wavePos_ = topLimit + (downLimit - topLimit) * 1 / 3;
		createWave(wavePos_);
		wavePos_ = topLimit + (downLimit - topLimit) * 2 / 3;
	}
	else if (rnd_ == 1) { // no medio
		wavePos_ = topLimit;
		createWave(wavePos_);
		wavePos_ = topLimit + (downLimit - topLimit) * 2 / 3;
	}
	else { // no abajo
		wavePos_ = topLimit + (downLimit - topLimit) * 1 / 3;
		createWave(wavePos_);
		wavePos_ = topLimit;
	}
	lastWave_ = createWave(wavePos_)->getComponent<Transform>(TRANSFORM_H);
}

Entity* WaterBossIA::createWave(float y) {
	Vector2D pos = Vector2D(WIN_WIDTH, y);
	Entity* wave = mngr_->addEntity();
	wave->addComponent<Transform>(TRANSFORM_H, pos, WAVE_WIDTH, (downLimit - topLimit) / 3, 1, 4)->setDir(Vector2D(-1, 0));
	wave->addComponent<Image>(IMAGE_H, &sdlutils().images().at("waves"));
	wave->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	wave->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 25), (downLimit - topLimit) / 3 - 25, WAVE_WIDTH);
	wave->addComponent<DisableOnExit>(DISABLEONEXIT_H);
	wave->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, wave, player_);
	return wave;
}