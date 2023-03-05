#include "Image.h"
#include "../Entities/EnemyBEU.h"

Image::Image(Texture* tex, int width, int height, Transform* trans) {
	frames_ = 0;
	fila_ = 0;
	framesTotales_ = 0;
	widthFrame_ = width;
	heightFrame_ = height;
	tr_ = trans;
	tex_ = tex;
}

Image::Image(Texture* tex, int nframes, int framesT, int fila, int widthFrame, int heightFrame) : tr_(nullptr), tex_(tex) { // Constructora
	frames_ = nframes;
	fila_ = fila;
	framesTotales_ = framesT;
	widthFrame_ = widthFrame;
	heightFrame_ = heightFrame;
}
// Destructora
Image::~Image() { }

void Image::initComponent() { 	// Inicializa el componente
	if(tr_ == nullptr)tr_ = ent_->getComponent<Transform>(int(TRANSFORM_H));
	assert(tr_ != nullptr);


}

void Image::update() {

}

// Dibuja en escena
void Image::render() {
	if (frames_ == 0) { //Cuando la imagen solo tiene un frame (sin animación)
		a = { tr_->getPos().getX() - ent_->mngr_->camRect_.x, tr_->getPos().getY() - ent_->mngr_->camRect_.y };
		SDL_Rect dest = build_sdlrect(a, tr_->getW(), tr_->getH());
		tex_->render(dest, tr_->getR());
	}
	else {
		SDL_Rect rect;
		rect.x = tr_->getPos().getX() - ent_->mngr_->camRect_.x;
		rect.y = tr_->getPos().getY() - ent_->mngr_->camRect_.y;
		rect.h = tr_->getH();
		rect.w = tr_->getW();
		SDL_Rect src;
		src.x = i * widthFrame_;
		src.y = heightFrame_ * fila_;
		src.h = heightFrame_;
		src.w = widthFrame_;
		tex_->render(src, rect, 0, nullptr, s);
		if (cont >= 5) {
			i++;
			cont = 0;
		}
		if (ent_->hasComponent(INPUTCOMPONENTBEU_H)) {
			cout << animPlaying << endl;
		}
		cont++;
		if (i >= frames_||i>=tope) {
			i = 0;
			animPlaying = false;
			fila_ = 0;
			if (ent_->hasComponent(INPUTCOMPONENTBEU_H)) {
				frames_ = 8;
			}
		}
	}
}


//matriz
void Image::setAnim(bool Anim, int Fila, int Frames, int I,int tope) { //Metodo generico para cambiar de animacion en BEU
	if (fila_ != Fila && !animPlaying) { // Si la animacion no es la actual la actualiza
		animPlaying = Anim;
		fila_ = Fila;
		frames_ = Frames;
		i = I;
		cont = 0;
		this->tope = tope;
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
