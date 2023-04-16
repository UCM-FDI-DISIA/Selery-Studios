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
	offset = 200;
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	downLimit = sdlutils().height();
	topLimit = sdlutils().height()* 0.55;

	attackIcePos_ = WIN_WIDTH / 2 - (tr_->getW() * tr_->getS())/ 2;
	attackWavesPos_ = WIN_WIDTH * 7 / 11;

	iceCont_ = 0;// al principio el contador estar� a 0
}

void WaterBossIA::update() {
	if (currentState_ == NONE) {// no ataca
		if (!(abs(tr_->getPos().getX() - (WIN_WIDTH * 3 / 4 -WATERBOSS_WIDTH)) >= 3)) {
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
				if (lastWave_ == nullptr || lastWave_->getPos().getX() < WIN_WIDTH - ICEBLOCK_WIDTH - offset) {
					summonWave();
					cont++;
					// numero de olas
					if (cont > 4) {
						currentState_ = NONE;
						chrono = sdlutils().currRealTime() + 3000;
						cont = 0;
						dir_ = Vector2D((WIN_WIDTH * 3 / 4 -(tr_->getW() * tr_->getS())) - tr_->getPos().getX(), 0).normalize();
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
					//im_->setAnim("waterBoss", 4, false, fila_);
					im_->setAnim("waterBoss", 6, false, fila_);
					set_ = true;
				}

				// esto tiene que ir dentro de un condicional de si est� en la animaci�n del ataque
				if (fila_ == 5 && !im_->isAnimPlaying()) {
					fila_ = 6; 
					//im_->setAnim("waterBoss", 21, false, fila_);
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
						int rnd = rand() % 4;
						rnd += 2;// n�mero de car�mbanos aleatorio entre 2 y 6
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
					dir_ = Vector2D(tr_->getPos().getX() - (WIN_WIDTH * 3 / 4 - (tr_->getW() * tr_->getS())), 0).normalize();
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
		wavePos_ = topLimit + (downLimit - topLimit) * 1 / 3;
		createWave(wavePos_);
		wavePos_ = topLimit + (downLimit - topLimit) - ICEBLOCK_HEIGHT;
	}
	else if (rnd_ == 1) { // no medio
		wavePos_ = topLimit;
		createWave(wavePos_);
		wavePos_ = topLimit + (downLimit - topLimit) -ICEBLOCK_HEIGHT;
	}
	else { // no abajo
		wavePos_ = topLimit + (downLimit - topLimit) * 1 / 3;
		createWave(wavePos_);
		wavePos_ = topLimit;
	}
	lastWave_ = createWave(wavePos_)->getComponent<Transform>(TRANSFORM_H);
	sdlutils().soundEffects().at("iceBlock").play();
}

Entity* WaterBossIA::createWave(float y) {
	Vector2D pos = Vector2D(WIN_WIDTH, y);
	Entity* wave = mngr_->addEntity();
	wave->addComponent<Transform>(TRANSFORM_H, pos, ICEBLOCK_WIDTH, ICEBLOCK_HEIGHT, 1, 4)->setDir(Vector2D(-1, 0));
	wave->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("iceBlock"), ICEBLOCK_WIDTH, ICEBLOCK_HEIGHT, 8);
	wave->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	wave->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), ICEBLOCK_HEIGHT, ICEBLOCK_WIDTH);
	wave->addComponent<DisableOnExit>(DISABLEONEXIT_H);
	wave->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, wave, player_);
	return wave;
}

void WaterBossIA::addIce(int n) {
	for (int i = 0; i < n; i++)cout << "car�mbano " << endl;
}