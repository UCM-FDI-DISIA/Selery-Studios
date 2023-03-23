#pragma once
#ifndef FRAMEDIMAGE_H
#define FRAMEDIMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 
#include "../utils/Entity.h"

class FramedImage : public Component {
private:
	int frames_, col = 0, widthFrame_, heightFrame_;
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	SDL_RendererFlip s = SDL_FLIP_NONE;
	SDL_Rect dest, src;
public:

	//Constructora
	FramedImage(Texture* tex, int width, int height, int frames);
	//FramedImage(Texture* tex, int nframes, int framesT, int fila, int widthFrame, int heightFrame);//Constructora
	//FramedImage(Texture* tex, int nframes, int framesT, int fila, int widthFrame, int heightFrame, string type);//Constructora

	// Destructora
	virtual ~FramedImage();

	void initComponent();

	void update();

	// Dibuja en escena
	void render();

	inline int getCol() { return col; }
	inline int getLastFrame() { return frames_; }

	void setAnim(string textureKey, int frames); //Metodo generico para cambiar de animacion
	//matriz
	//void setAnim(bool Anim, int Fila, int Frames, int I, int tope); //Metodo generico para cambiar de animacion en BEU

	//void setAnimTexture(string textureKey, int Frames, int Width, int Fila = 0);

	////spritesheet
	//void setSpriteAnim(bool Anim, int Frames, int I, Texture* t); //Metodo generico para cambiar de animacion en BEU

	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }

	SDL_RendererFlip  getFlip() { return s; }
};
#endif

