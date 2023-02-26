#include "Image.h"
#include "../Entities/EnemyBEU.h"

Image::Image(Texture* tex, int nframes, int framesT, int fila) : tr_(nullptr), tex_(tex) { // Constructora
	frames_ = nframes;
	fila_ = fila;
	framesTotales_ = framesT;
}
// Destructora
Image::~Image() { }

void Image::initComponent() { 	// Inicializa el componente
	tr_ = ent_->getComponent<Transform>(int(TRANSFORM_H));
	isPlayerTD = ent_->hasComponent(INPUTCOMPONENT_H);
	isPlayerBEU = ent_->hasComponent(INPUTCOMPONENTBEU_H);
	//isEnemyBEU = ent_->hasComponent(ENEMYBEUDIRECTIONCOMPONENT_H);
	assert(tr_ != nullptr);


}

void Image::update() {
	if (isPlayerTD) {
		//cout << vel.getX() << " " << vel.getY() << endl;
		if (tr_->getDir().getX() == 1 && tr_->getDir().getY() == 0) {
			tex_ = &SDLUtils::instance()->images().at("p_left");
			framesTotales_ = 7;
			//s = SDL_FLIP_NONE;
			tr_->setW(476);
		}
		else if (tr_->getDir().getX() == -1 && tr_->getDir().getY() == 0) {
			tex_ = &SDLUtils::instance()->images().at("p_right");
			framesTotales_ = 7;
			//	s = SDL_FLIP_HORIZONTAL;
			tr_->setW(476);
		}
		else if (tr_->getDir().getY() == -1 && tr_->getDir().getX() == 0) {
			tex_ = &SDLUtils::instance()->images().at("p_top");

			framesTotales_ = 9;
			tr_->setW(612);
		}
		else if (tr_->getDir().getY() == 1 && tr_->getDir().getX() == 0) {
			tex_ = &SDLUtils::instance()->images().at("p_down");
			framesTotales_ = 9;
			tr_->setW(612);
		}
		else {
			tex_ = &SDLUtils::instance()->images().at("p_idle");
			framesTotales_ = 7;
			tr_->setW(519);
		}
		s = SDL_FLIP_NONE;
	}
	/*if (isEnemyBEU) *///static_cast<EnemyBEU*>(ent_)->setAttackBool(false);
}

// Dibuja en escena
void Image::render() {
	if (frames_ == 0) { //Cuando la imagen solo tiene un frame (sin animación)
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(dest, tr_->getR());
	}
	else {
		SDL_Rect rect;
		rect.x = tr_->getPos().getX();
		rect.y = tr_->getPos().getY();
		rect.h = tr_->getH();
		rect.w = tr_->getW() / framesTotales_;
		SDL_Rect src;
		src.x = i * (tr_->getW() / framesTotales_);
		src.y = tr_->getH() * fila_;
		src.h = tr_->getH();
		src.w = tr_->getW() / framesTotales_;
		tex_->render(src, rect, 0, nullptr, s);
		if (cont >= 10) {
			i++;
			cont = 0;
		}
		cont++;
		if (i >= frames_) {
			i = 0;
			animPlaying = false;
			fila_ = 0;
			static_cast<EnemyBEU*>(ent_)->setAttackBool(false);
		}
	}
}


//matriz
void Image::setAnim(bool Anim, int Fila, int Frames, int I) { //Metodo generico para cambiar de animacion en BEU
	if (fila_ != Fila && !animPlaying) { // Si la animacion no es la actual la actualiza
		animPlaying = Anim;
		fila_ = Fila;
		frames_ = Frames;
		i = I;
		cont = 0;
	}
}

//spritesheet
void Image::setSpriteAnim(bool Anim, int Frames, int I, Texture* t) { //Metodo generico para cambiar de animacion en BEU
	if (!animPlaying) { // Si la animacion no es la actual la actualiza
		animPlaying = Anim;
		fila_ = 0;
		frames_ = Frames;
		i = I;
		cont = 0;
		tex_ = t;
	}
}