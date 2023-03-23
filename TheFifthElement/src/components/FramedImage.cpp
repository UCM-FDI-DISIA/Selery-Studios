#include "FramedImage.h"

FramedImage::FramedImage(Texture* tex, int width, int height, int frames) {
	widthFrame_ = width;
	heightFrame_ = height;
	tex_ = tex;
	frames_ = frames;
}


//FramedImage::FramedImage(Texture* tex, int nframes, int framesT, int fila, int widthFrame, int heightFrame, string type) : tr_(nullptr), tex_(tex) { // Constructora
//	frames_ = nframes;
//	fila_ = fila;
//	framesTotales_ = framesT;
//	widthFrame_ = widthFrame;
//	heightFrame_ = heightFrame;
//	type_ = type;
//}
//
//FramedImage::FramedImage(Texture* tex, int nframes, int framesT, int fila, int widthFrame, int heightFrame) : tr_(nullptr), tex_(tex) { // Constructora
//	frames_ = nframes;
//	fila_ = fila;
//	framesTotales_ = framesT;
//	widthFrame_ = widthFrame;
//	heightFrame_ = heightFrame;
//}

// Destructora
FramedImage::~FramedImage() { }

void FramedImage::initComponent() { 	// Inicializa el componente
	if (tr_ == nullptr)tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	assert(tr_ != nullptr);
}

void FramedImage::update() {
	SDL_Rect dest;
	dest.x = tr_->getPos().getX() - mngr_->camRect_.x;
	dest.y = tr_->getPos().getY() - mngr_->camRect_.y;
	dest.h = tr_->getH() * tr_->getS();
	dest.w = tr_->getW() * tr_->getS();
	SDL_Rect src;
	src.x = col * widthFrame_;
	src.y = heightFrame_;
	src.h = heightFrame_;
	src.w = widthFrame_;

	if (col >= frames_) {
		col = 0;
	}
}

// Dibuja en escena
void FramedImage::render() {
	tex_->render(src, dest, 0, nullptr, s);
}

void FramedImage::setAnim(string textureKey, int frames) {
	tex_ = &sdlutils().images().at(textureKey);
	frames_ = frames;
}

//matriz
//void FramedImage::setAnim(bool Anim, int Fila, int Frames, int I, int tope) { //Metodo generico para cambiar de animacion en BEU
//	if (fila_ != Fila && !animPlaying) { // Si la animacion no es la actual la actualiza
//		animPlaying = Anim;
//		fila_ = Fila;
//		frames_ = Frames;
//		i = I;
//		cont = 0;
//		this->tope = tope;
//	}
//}
//
//void FramedImage::setAnimTexture(string textureKey, int Frames, int Width, int Fila) { //Metodo generico para cambiar de Textura (el width es temporal no deberia ser el with de la imagen sino de la entidad)
//	Texture* nT = &sdlutils().images().at(textureKey);
//	if (nT != tex_) { // Si la animacion no es la actual la actualiza
//		tex_ = nT;
//		frames_ = Frames;
//		tr_->setW(Width);
//		fila_ = Fila;
//	}
//}
//
////spritesheet
//void FramedImage::setSpriteAnim(bool Anim, int Frames, int I, Texture* t) { //Metodo generico para cambiar de animacion en BEU
//	if (!animPlaying) { // Si la animacion no es la actual la actualiza
//		animPlaying = Anim;
//		fila_ = 0;
//		frames_ = Frames;
//		i = I;
//		cont = 0;
//		tex_ = t;
//	}
//}