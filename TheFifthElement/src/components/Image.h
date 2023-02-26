#pragma once
#ifndef IMAGE_H
#define IMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 
#include "../utils/Entity.h"
#include "../Entities/PlayerBEU.h"
//#include "../Entities/EnemyBEU.h"

class Image : public Component {

private:
	int frames_, fila_, framesTotales_;
	int i = 0;
	int cont = 0;

	
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	bool isPlayerTD = false;
	bool isPlayerBEU = false;
	bool isEnemyBEU = false;
	
	SDL_RendererFlip s = SDL_FLIP_NONE;
	bool animPlaying = false;

public:
<<<<<<< Updated upstream

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
		isPlayerTD = ent_->hasComponent(INPUTCOMPONENT_H);
		isPlayerBEU = ent_->hasComponent(INPUTCOMPONENTBEU_H);
		assert(tr_ != nullptr);
=======
	//Constructora
	Image(Texture* tex, int nframes, int framesT, int fila);//Constructora

	// Destructora
	virtual ~Image();

	void initComponent();
>>>>>>> Stashed changes

	void update();

	// Dibuja en escena
	void render();

	inline int getRow() { return fila_; }
	inline int getLastFrame(){ return frames_;}

	//matriz
	void setAnim(bool Anim, int Fila, int Frames, int I); //Metodo generico para cambiar de animacion en BEU

	//spritesheet
	void setSpriteAnim(bool Anim, int Frames, int I, Texture* t); //Metodo generico para cambiar de animacion en BEU

	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }
	bool isAnimPlaying() { return animPlaying; }
};
#endif