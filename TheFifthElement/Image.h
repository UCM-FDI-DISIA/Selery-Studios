#pragma once
#ifndef IMAGE_H
#define IMAGE_H_
#include "sdlutils/Texture.h"
#include "Transform.h" 
#include "utils/Entity.h"
class Image : public Component {
public:
	int i = 0;
	int cont = 0;

	// Constructora
	Image(Texture* tex,int nframes) : tr_(nullptr), tex_(tex) {
		frames_ = nframes;
	}
	// Destructora
	virtual ~Image() { }
	// Inicializa el componente
	//void initComponent() override;
	// Dibuja
	//void render() override;
	// Inicializa el componente
	void initComponent() {
		tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
		assert(tr_ != nullptr);
	}
	// Dibuja en escena
	void render() {
		if (frames_ == 1) { //Cuando la imagen solo tiene un frame (sin animación)
			SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
			tex_->render(dest, tr_->getR());
		}
		else {
			SDL_Rect rect;
			rect.x = tr_->getPos().getX();
			rect.y = tr_->getPos().getY();
			rect.h = tr_->getH();
			rect.w = tr_->getW() / frames_;
			SDL_Rect src;
			src.x = i*(tr_->getW() / frames_);
			src.y = 0;
			src.h = tr_->getH();
			src.w = tr_->getW() / frames_;
			tex_->render(src, rect);
			if (cont >= 5) {
				i++;
				cont = 0;
			}
			cont++;
			if (i ==frames_) i = 0;
		}
		
	}
private:
	int frames_;
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
};
#endif