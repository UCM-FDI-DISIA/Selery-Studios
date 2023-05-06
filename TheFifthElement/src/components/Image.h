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
	string texKey_ = "";
public:
	//Constructora
	Image(Texture* tex);

	// Destructora
	virtual ~Image();

	void initComponent();

	// Dibuja en escena
	void render();

	inline void setTexture(string key) { 
		tex_ = &SDLUtils::instance()->images().at(key);
		texKey_ = key;
	}

	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }

	inline string getTexKey() { return texKey_; }
};
#endif