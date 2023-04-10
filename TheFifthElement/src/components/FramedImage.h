#pragma once
#ifndef FRAMEDIMAGE_H
#define FRAMEDIMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 
#include "../utils/Entity.h"
#include "../sdlutils/SDLUtils.h"

class FramedImage : public Component {
private:
	int frames_, col = 0, widthFrame_, heightFrame_, cont = 0,tope =100;
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	SDL_RendererFlip s = SDL_FLIP_NONE;
	SDL_Rect dest, src;
	bool isAnimUnstoppable_ = false;
	string type_, texKey_ = "";
public:
	//Constructora
	FramedImage(Texture* tex, int width, int height, int frames, string type = "");
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

	void setAnim(string textureKey, int frames, bool isAnimUnstoppable); //Metodo generico para cambiar de animacion
	void setAnim(string textureKey, int col,int frames, bool isAnimUnstoppable); //Metodo generico para cambiar de animacion


		inline void setTope(int i) { tope = i; }
		inline int getTope() const { return tope; }

	inline bool getIsAnimUnstoppable() { return isAnimUnstoppable_; }

	inline void setType(string newValue) { type_ = newValue; }
	inline string getType() { return type_; }

	inline string getTexKey() { return texKey_; }

	inline void setIsAnimUnstoppable(bool newValue) { isAnimUnstoppable_ = newValue; }
	//matriz
	//void setAnim(bool Anim, int Fila, int Frames, int I, int tope); //Metodo generico para cambiar de animacion en BEU

	//void setAnimTexture(string textureKey, int Frames, int Width, int Fila = 0);

	////spritesheet
	//void setSpriteAnim(bool Anim, int Frames, int I, Texture* t); //Metodo generico para cambiar de animacion en BEU

	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }

	SDL_RendererFlip  getFlip() { return s; }
};
#endif

