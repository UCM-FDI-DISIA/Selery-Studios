#include "FramedImage.h"

FramedImage::FramedImage(Texture* tex, int width, int height, int frames, string type) {
	widthFrame_ = width;
	heightFrame_ = height;
	tex_ = tex;
	frames_ = frames;
	type_ = type;
	fila_ = 0;
	framesPerRow_ = frames;
}

FramedImage::FramedImage(Texture* tex, int width, int height, int frames, int fila, string type) {
	widthFrame_ = width;
	heightFrame_ = height;
	tex_ = tex;
	frames_ = frames;
	type_ = type;
	fila_ = fila;
	framesPerRow_ = frames;
}

// Destructora
FramedImage::~FramedImage() { }

void FramedImage::initComponent() { 	// Inicializa el componente
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	if (ent_->hasComponent(SKINBEUCOMPONENT_H))
	{
		frameRate = FRAME_RATE_BEU_PLAYER;
	}
}

void FramedImage::update() {
	dest.x = tr_->getPos().getX() - mngr_->camRect_.x;
	dest.y = tr_->getPos().getY() - mngr_->camRect_.y;
	dest.h = (tr_->getH() * tr_->getSize() * WIN_HEIGHT) / 600;
	dest.w = (tr_->getW() * tr_->getSize() * WIN_WIDTH) / 900;
	src.x = col * widthFrame_;
	src.y = fila_ * heightFrame_;
	src.h = heightFrame_;
	src.w = widthFrame_;

	if (col >= frames_ - 1 || col >= tope) {
		col = 0;
		isAnimUnstoppable_ = false;
		if (ent_->hasComponent(LIGHTBOSSELEMENT_H) && !ent_->hasComponent(DISABLEONEXIT_H)) //he metido esto específico del rayo del lightboss como apaño temporal hasta que encuentre una solucion mas elegante
		{
			ent_->setAlive(false);
		}
	}
	else if (cont > frameRate) {
		col++;
		cont = 0;
	}
	cont++;

	/*if (col >= framesPerRow_ - 1) { //esta parte la ha comentado CAO porque al estar aqui abajo por orden de ejecucion nunca se ejecutará el codigo del primer if, hay que echar un ojo
		col = 0;
		fila_++;
	}
	if (fila_ >= nFilas_) {
		fila_ = 0;
		isAnimUnstoppable_ = false;
	}*/
}

// Dibuja en escena
void FramedImage::render() {
	tex_->render(src, dest, 0, nullptr, s);
}

void FramedImage::setAnim(string textureKey, int frames, bool isAnimUnstoppable, int fila) {
	if (!isAnimUnstoppable_) {
		tex_ = &SDLUtils::instance()->images().at(textureKey);
		texKey_ = textureKey;
		frames_ = frames;
		isAnimUnstoppable_ = isAnimUnstoppable;
		fila_ = fila;
	}
}


void FramedImage::setAnim(string textureKey, int col_, int frames, bool isAnimUnstoppable, int fila) {
	if (!isAnimUnstoppable_) {
		tex_ = &SDLUtils::instance()->images().at(textureKey);
		texKey_ = textureKey;
		frames_ = frames;
		isAnimUnstoppable_ = isAnimUnstoppable;
		col = col_;
		fila_ = fila;
	}
}

void FramedImage::setAnim(string textureKey, int frames, int framesPerRow, int nFilas, bool isAnimUnstoppable, int fila) {
	if (!isAnimUnstoppable_) {
		tex_ = &SDLUtils::instance()->images().at(textureKey);
		texKey_ = textureKey;
		frames_ = frames;
		framesPerRow_ = framesPerRow;
		isAnimUnstoppable_ = isAnimUnstoppable;
		fila_ = fila;
		nFilas_ = nFilas;
	}
}