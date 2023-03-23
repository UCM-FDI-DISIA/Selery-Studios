#pragma once
#ifndef IMAGE_H
#define IMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 
#include "../utils/Entity.h"

class Image : public Component {
private:
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	SDL_RendererFlip s = SDL_FLIP_NONE;
public:
	//Constructora
	Image(Texture* tex);

	// Destructora
	virtual ~Image();

	void initComponent();

	void update();

	// Dibuja en escena
	void render();


	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }
};
#endif