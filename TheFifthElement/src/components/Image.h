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
	float scale_ = WIN_WIDTH / 900;

	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	bool isPlayerTD;
	bool isPlayerBEU;
	bool isEnemyBEU;
	SDL_RendererFlip s = SDL_FLIP_NONE;
	bool animPlaying = false;
	int widthFrame_, heightFrame_;
	int tope = 100;
	Vector2D a;

	string type_ = "";
public:

	//Constructora
	Image(Texture* tex, int width, int height, Transform* trans);
	Image(Texture* tex, int nframes, int framesT, int fila, int widthFrame, int heightFrame);//Constructora
	Image(Texture* tex, int nframes, int framesT, int fila, int widthFrame, int heightFrame, string type);//Constructora

	// Destructora
	virtual ~Image();

	void initComponent();

	void update();

	// Dibuja en escena
	void render();

	inline int getCol() { return i; }
	inline int getRow() { return fila_; }
	inline int getLastFrame() { return frames_; }
	inline void setTope(int i) { tope = i; }
	inline int getTope() const { return tope; }

	inline void setType(string type) { type_ = type; }
	inline string getType() { return type_; }
	

	//matriz
	void setAnim(bool Anim, int Fila, int Frames, int I, int tope); //Metodo generico para cambiar de animacion en BEU

	void setAnimTexture(string textureKey, int Frames, int Width, int Fila = 0);

	//spritesheet
	void setSpriteAnim(bool Anim, int Frames, int I, Texture* t); //Metodo generico para cambiar de animacion en BEU

	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }

	SDL_RendererFlip  getFlip() { return s; }
	inline bool isAnimPlaying() { return animPlaying; }
	inline void setAnimPlaying(bool b) { animPlaying = b; }
};
#endif