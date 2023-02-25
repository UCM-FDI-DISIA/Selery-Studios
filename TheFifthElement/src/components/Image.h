#pragma once
#ifndef IMAGE_H
#define IMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 
#include "../utils/Entity.h"
#include "InputComponentBEU.h"
#include "../Entities/PlayerBEU.h"
//#include "../components/ColliderComponent.h"
//class ColliderComponent;
class Image : public Component {

private:
	int frames_, fila_, framesTotales_;
	int i = 0;
	int cont = 0;

	
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	//ColliderComponent* col_ = nullptr;
	bool isPlayerTD = false;
	bool isPlayerBEU = false;
	
	SDL_RendererFlip s = SDL_FLIP_NONE;
	bool animPlaying = false;

public:

	// Constructora
	Image(Texture* tex, int nframes, int framesT, int fila) : tr_(nullptr), tex_(tex) {
		frames_ = nframes;
		fila_ = fila;
		framesTotales_ = framesT;
	}
	// Destructora
	virtual ~Image() { }
	// Inicializa el componente
	//void initComponent() override;
	// Dibuja
	//void render() override;
	// Inicializa el componente
	void initComponent() {
		tr_ = ent_->getComponent<Transform>(int(TRANSFORM_H));
		/*if (ent_->hasComponent(COLLIDERCOMPONENT_H))
			col_ = ent_->getComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H));*/

		isPlayerTD = ent_->hasComponent(INPUTCOMPONENT_H);
		isPlayerBEU = ent_->hasComponent(INPUTCOMPONENTBEU_H);
		assert(tr_ != nullptr);

		
	}

	void update() {
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
				//if (col_ != nullptr) { col_->setOffset(Vector2D(75, 40)); }
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
		else if (isPlayerBEU && !animPlaying) {
			
			if (!(static_cast<PlayerBEU*>(ent_)->getAttack())){
				if (tr_->getDir().getX() == 1 && (fila_ != 1||s==SDL_FLIP_HORIZONTAL)) {
					fila_ = 1;
					//tex_ = &SDLUtils::instance()->images().at("p_left");
					frames_ = 8;
					s = SDL_FLIP_NONE;
					cont = 0;
					i = 0;
					
				}
				else if (tr_->getDir().getX() == -1 && (fila_ != 1||s==SDL_FLIP_NONE)) {
					//tex_ = &SDLUtils::instance()->images().at("p_right");
					fila_ = 1;
					frames_ = 8;
					s = SDL_FLIP_HORIZONTAL;
					cont = 0;
					i = 0;
					
				}
				else if (fila_ != 0 && tr_->getDir().getX() == 0) {
					//tex_ = &SDLUtils::instance()->images().at("p_idle");
					fila_ = 0;
					frames_ = 8;
					i = 0;
					cont = 0;
					
				}
			}
		}
	}

	// Dibuja en escena
	void render() {
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
			src.x = i*(tr_->getW() / framesTotales_);
			src.y = tr_->getH() * fila_;
			src.h = tr_->getH();
			src.w = tr_->getW() / framesTotales_;
			tex_->render(src, rect,0,nullptr,s);
			if (cont >= 5) {
				i++;
				cont = 0;
			}
			cont++;
			if (i == frames_) { 
				i = 0;
				if (static_cast<PlayerBEU*>(ent_)->getAttack()) {
					
					//ent_->getComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H)->stop_attack();
					static_cast<PlayerBEU*>(ent_)->setAttack(false);
				}
				if (animPlaying) { animPlaying = false;	static_cast<PlayerBEU*>(ent_)->setAttack(false);
				}
			}
		}
	}

	inline int getRow() { return fila_; }
	inline int getLastFrame(){ return frames_;}

	void setAnim(bool Anim, int Fila, int Frames, int I, int Cont) { //Metodo generico para cambiar de animacion en BEU
		if (fila_ != Fila && !animPlaying) { // Si la animacion no es la actual la actualiza
			animPlaying = Anim;
			fila_ = Fila;
			frames_ = Frames;
			i = I;
			cont = Cont;
		}
	}

	/*inline Texture* getTexture*/

	bool isAnimPlaying() {
		return animPlaying;
	}

};
#endif