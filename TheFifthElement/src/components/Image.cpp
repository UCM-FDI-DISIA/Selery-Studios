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
	assert(tr_ != nullptr);


}

void Image::update() {
	
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
		if (cont >= 5) {
			i++;
			cont = 0;
		}
		cont++;
		if (i >= frames_) {
			i = 0;
			animPlaying = false;
			fila_ = 0;
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

void Image::setAnimTexture(string textureKey, int Frames, int Width) { //Metodo generico para cambiar de Textura (el width es temporal no deberia ser el with de la imagen sino de la entidad)
	Texture* nT = &sdlutils().images().at(textureKey);
	if (nT != tex_) { // Si la animacion no es la actual la actualiza
		tex_ = nT;
		framesTotales_ = Frames;
		tr_->setW(Width);
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
