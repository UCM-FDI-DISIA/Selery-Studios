#pragma once
#ifndef IMAGE_H
#define IMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 
#include "../utils/Entity.h"

class Image : public Component {
private:
	int frames_, fila_, framesTotales_;
	int i = 0;
	int cont = 0;

	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	
	SDL_RendererFlip s = SDL_FLIP_NONE;
	bool animPlaying = false;

public:

	//Constructora
	Image(Texture* tex, int nframes, int framesT, int fila);//Constructora

	// Destructora
	virtual ~Image();

	void initComponent();

	void update();

	// Dibuja en escena
	void render();

	inline int getRow() { return fila_; }
	inline int getLastFrame(){ return frames_;}

	//matriz
	void setAnim(bool Anim, int Fila, int Frames, int I); //Metodo generico para cambiar de animacion en BEU
	void setAnimTexture(string textureKey, int Frames, int Width);

	//spritesheet
	void setSpriteAnim(bool Anim, int Frames, int I, Texture* t); //Metodo generico para cambiar de animacion en BEU

	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }
	inline bool isAnimPlaying() { return animPlaying; }
};
#endif